#include "simulation.h"


//----------- Variabili extern 
extern int 					end;
extern state_t				state_pc;
extern pthread_mutex_t		mux_state_pc;
extern state_t 				state_board;
extern pthread_mutex_t 		mux_state_board;
extern ref_t				ref_pc;
extern pthread_mutex_t		mux_ref_pc;
extern par_ctrl_t 			par_ctrl_pc;
extern pthread_mutex_t		mux_par_ctrl_pc;
extern int 					dl_miss_control;
extern int 					dl_miss_state_update;
extern int 					dl_miss_comboard;
extern int 					dl_miss_compc;
extern dn_t                 dn;
extern pthread_mutex_t		mux_dn;
extern par_dn_t             par_dn_pc;
extern pthread_mutex_t		mux_par_dn;
extern unsigned int         period_ctrl;
#ifdef EXTIME
extern int ex_time[6];
extern int wc_extime[6];
extern struct timespec monotime_i[6], monotime_f[6];
extern int ex_cnt[6];
extern long ex_sum[6];
#endif

//---------------- Variabili Board
inout_t inout_board=
{	CNT_ALPHA_0,
	CNT_THETA_0,
	CCR_0,
};
pthread_mutex_t mux_inout_board = PTHREAD_MUTEX_INITIALIZER;
par_ctrl_t par_ctrl_board = // parametri per il controllo scheda
{	KP_UP_ALPHA_DEF,
	KP_UP_THETA_DEF,
	KD_UP_ALPHA_DEF,
	KD_UP_THETA_DEF,
	KP_DOWN_ALPHA_DEF,
	KD_DOWN_ALPHA_DEF,
	DPOLE_REF_DEF,
	REF_GEN_NUM_DEF,
	REF_GEN_DEN_DEF
};
pthread_mutex_t mux_par_ctrl_board = PTHREAD_MUTEX_INITIALIZER;		// mutual exclusion per par_control
ref_t ref_board = {ALPHA_REF, THETA_REF, SWINGUP_DEF};		// struct riferimento 
pthread_mutex_t mux_ref_board = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per ref

//---------- Variabili Buffer
state_t state_buffer=
{	ALPHA_0,
	THETA_0,
	VOLTAGE_0
}; 	
par_ctrl_t par_ctrl_buffer =
{	KP_UP_ALPHA_DEF,
	KP_UP_THETA_DEF,
	KD_UP_ALPHA_DEF,
	KD_UP_THETA_DEF,
	KP_DOWN_ALPHA_DEF,
	KD_DOWN_ALPHA_DEF,
	DPOLE_REF_DEF,
	REF_GEN_NUM_DEF,
	REF_GEN_DEN_DEF
};
ref_t ref_buffer = 
{	ALPHA_REF,
	THETA_REF,
	SWINGUP_DEF
};					// struct riferimento 
pthread_mutex_t 	mux_buffer = PTHREAD_MUTEX_INITIALIZER;

//---------- Variabili MATLAB
par_ctrl_t par_ctrl;
par_dn_t par_dn;
DW_fast_T fast_DW;
DW_slow_T slow_DW;
PrevZCX_slow_T slow_PrevZCX;

//----------- state_update
void* state_update(void* arg){
    cpu_set(2);
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	// init
	uint16_T rtb_Cast2[2];
	uint16_T CCR_local;
	dn_t dn_local;
	physics_Init();
	
	while(!end){
#ifdef EXTIME
        start_extime(0, PERIOD_STATE_UPDATE);
#endif
		pthread_mutex_lock(&mux_dn);
			dn_local = dn;
		pthread_mutex_unlock(&mux_dn);
		pthread_mutex_lock(&mux_inout_board);
			CCR_local = inout_board.CCR;
		pthread_mutex_unlock(&mux_inout_board);
		
		physics(CCR_local, dn_local.dist, dn_local.noise, rtb_Cast2);
		
		pthread_mutex_lock(&mux_inout_board);
			inout_board.CNT_alpha = rtb_Cast2[0];
			inout_board.CNT_theta = rtb_Cast2[1];
		pthread_mutex_unlock(&mux_inout_board);
		
		// end task
		if(deadline_miss(id)){
			dl_miss_state_update+=1;
		}
#ifdef EXTIME
        stop_extime(0);
#endif
		wait_for_period(id);		// wait to next period
	}
	return 0;
}

//---------- control
void* control(void* arg){
    cpu_set(1);
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);

	//----------- Variabili locali
	uint16_T rtb_Cast2[2];
	uint16_T CCR_local;
	ref_t ref_local;
	real32_T rtb_rad_to_deg1[2]; // variabile locale che condiene il valore di alpha e theta in gradi.
	real32_T voltage;
	dn_t dn_local;
	
	// init
	controller_Init();
	disturbance_and_noise_Init(&slow_DW.dist);
	
	while(!end){
#ifdef EXTIME
        start_extime(1, period_ctrl);
#endif
		pthread_mutex_lock(&mux_par_ctrl_board);
			par_ctrl = par_ctrl_board;
		pthread_mutex_unlock(&mux_par_ctrl_board);
		pthread_mutex_lock(&mux_par_dn);
			par_dn = par_dn_pc;
		pthread_mutex_unlock(&mux_par_dn);
		pthread_mutex_lock(&mux_dn);
			dn_local.delay = dn.delay;
			dn_local.kick = dn.kick;
		pthread_mutex_unlock(&mux_dn);
		pthread_mutex_lock(&mux_ref_board);
			ref_local.alpha = ref_board.alpha;
            ref_local.swingup = ref_board.swingup;
		pthread_mutex_unlock(&mux_ref_board);
		pthread_mutex_lock(&mux_inout_board);
			rtb_Cast2[0] = inout_board.CNT_alpha;
			rtb_Cast2[1] = inout_board.CNT_theta;
		pthread_mutex_unlock(&mux_inout_board);

		controller(ref_local.alpha, ref_local.swingup, rtb_Cast2[0],
             rtb_Cast2[1], dn_local.delay, &ref_local.theta, rtb_rad_to_deg1,
             &voltage, &CCR_local);
		
		disturbance_and_noise(dn_local.kick, &slow_DW.dist, dn_local.noise);
		dn_local.dist = slow_DW.dist;
		
		pthread_mutex_lock(&mux_inout_board);
			inout_board.CCR = CCR_local;
		pthread_mutex_unlock(&mux_inout_board);
		pthread_mutex_lock(&mux_ref_board);
			ref_board.theta = ref_local.theta;
		pthread_mutex_unlock(&mux_ref_board);
		pthread_mutex_lock(&mux_dn);
			dn.dist = dn_local.dist;
			memcpy(&dn.noise, &dn_local.noise, sizeof dn.noise);
		pthread_mutex_unlock(&mux_dn);
		pthread_mutex_lock(&mux_state_board);
			state_board.alpha = rtb_rad_to_deg1[0];
			state_board.theta = rtb_rad_to_deg1[1];
			state_board.voltage = voltage;
		pthread_mutex_unlock(&mux_state_board);
		
		// end task
		if(deadline_miss(id)){
			dl_miss_control+=1;
		}
#ifdef EXTIME
        stop_extime(1);
#endif
		wait_for_period(id);		// wait to next period
	}
	
	return 0;
}

// task di comunicazione pc, scrive ref_pc e par_ctrl_pc su buffer, legge state da buffer
void* compc(void* arg){
    cpu_set(0);
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	while(!end){
#ifdef EXTIME
        start_extime(2, PERIOD_COMPC);
#endif
		pthread_mutex_lock(&mux_buffer);
			// scrittura di ref_pc su buffer
			pthread_mutex_lock(&mux_ref_pc);
				ref_buffer.alpha = ref_pc.alpha;
                ref_buffer.swingup = ref_pc.swingup;
                ref_pc.theta = ref_buffer.theta;
			pthread_mutex_unlock(&mux_ref_pc);
			// scrittura di par_ctrl_pc su buffer
			pthread_mutex_lock(&mux_par_ctrl_pc);
				par_ctrl_buffer = par_ctrl_pc;
			pthread_mutex_unlock(&mux_par_ctrl_pc);
			// lettura di state_buffer e scrittura state_pc
			pthread_mutex_lock(&mux_state_pc);
				state_pc = state_buffer;
			pthread_mutex_unlock(&mux_state_pc);
		pthread_mutex_unlock(&mux_buffer);
		
		
		// end task
		if(deadline_miss(id)){
			dl_miss_compc+=1;
		}
#ifdef EXTIME
        stop_extime(2);
#endif
		wait_for_period(id);		// wait to next period
	}
	return 0;
}

// task di comunicazione scheda, scrive state su buffer, legge par_control e ref da buffer
void* comboard(void* arg){
    cpu_set(1);
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	
	while(!end){
#ifdef EXTIME
        start_extime(3, PERIOD_COMBOARD);
#endif
		pthread_mutex_lock(&mux_buffer);
			// lettura di ref da buffer, scrittura di ref_board
			pthread_mutex_lock(&mux_ref_board);
				ref_board.alpha = ref_buffer.alpha;
				ref_board.swingup = ref_buffer.swingup;
                ref_buffer.theta = ref_board.theta;
			pthread_mutex_unlock(&mux_ref_board);
			// lettura di par_control da buffer, scrittura di par_ctrl_pc
			pthread_mutex_lock(&mux_par_ctrl_board);
				par_ctrl_board = par_ctrl_buffer;
			pthread_mutex_unlock(&mux_par_ctrl_board);
			// scrittura di inout_board su buffer
			pthread_mutex_lock(&mux_state_board);
				state_buffer = state_board;
			pthread_mutex_unlock(&mux_state_board);
		pthread_mutex_unlock(&mux_buffer);
		
		// end task
		if(deadline_miss(id)){
			dl_miss_comboard+=1;
		}
#ifdef EXTIME
        stop_extime(3);
#endif
		wait_for_period(id);		// wait to next period

	}
	return 0;
}

