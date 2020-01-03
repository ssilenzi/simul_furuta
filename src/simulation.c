#include "simulation.h"


//----------- Variabili extern 
extern int 					end;
//extern int 					brake;
//extern int 					swingup;
//extern pthread_mutex_t 		mux_brake;
extern state_pc_t			state_pc;
extern pthread_mutex_t 		mux_state_pc;
extern ref_t				ref_pc;
extern pthread_mutex_t		mux_ref_pc;
extern par_ctrl_t 			par_control_pc;
extern pthread_mutex_t 		mux_parcontr_pc;
extern int 					dl_miss_control;
extern int 					dl_miss_state_update;
extern int 					dl_miss_comboard;
extern int 					dl_miss_compc;

extern dn_t dn;
extern par_dn_t par_dn;



//---------------- Variabili Board
/*
 * State state_board=
	{ALPHA_0, 
	ALPHADOT_0,
	THETA_0,
	THETADOT_0,
	CURRENT_0,
	VOLTAGE_0,
	CCR_0,
	ENC_ALPHA_0,
	ENC_THETA_0
	}; 
*/

state_board_t state_board=
	{CNT_ALPHA_0,
	CNT_THETA_0,
	CCR_0,
	};

pthread_mutex_t 	mux_state_board = PTHREAD_MUTEX_INITIALIZER;

state_board_t 	state_board_reset =
	{CNT_ALPHA_0,
    CNT_THETA_0,
    CCR_0,
	};

par_ctrl_t par_control_board =
{KP_UP_ALPHA_DEF,
	KP_UP_THETA_DEF,
	KD_UP_ALPHA_DEF,
	KD_UP_THETA_DEF,
	KP_DOWN_ALPHA_DEF,
	KD_DOWN_ALPHA_DEF,
	DPOLE_REF,
	REF_GEN_NUM,
	REF_GEN_DEN}; // parametri per il controllo scheda
par_ctrl_t par_ctrl; // da rinominare nel file controller.c
	
	
/* OLD
Par_control par_control_board = 
	{KP_ALPHA_DEF, 
	KD_ALPHA_DEF, 
	KP_THETA_DEF, 
	KD_THETA_DEF, 
	KSU_DEF};	// struct con parametri del controllore
*/
pthread_mutex_t 	mux_parcontr_board = PTHREAD_MUTEX_INITIALIZER;		// mutual exclusion per par_control

//Ref ref_board;
//pthread_mutex_t 	mux_ref_board = PTHREAD_MUTEX_INITIALIZER;
ref_t ref_board = {ALPHA_REF, THETA_REF, SWINGUP_DEF};		// struct riferimento 
pthread_mutex_t 	mux_ref_board = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per ref

//---------- Variabili Buffer
/*
State state_buffer=
	{ALPHA_0, 
	ALPHADOT_0,
	THETA_0,
	THETADOT_0,
	CURRENT_0,
	VOLTAGE_0,
	CCR_0,
	CNT_ALPHA_0,
	CNT_THETA_0
	}; 
	*/
state_pc_t state_buffer=
{	ALPHA_0,
	THETA_0,
	VOLTAGE_0
}; 	
pthread_mutex_t 	mux_state_buffer = PTHREAD_MUTEX_INITIALIZER;

par_ctrl_t par_control_buffer =
{KP_UP_ALPHA_DEF,
	KP_UP_THETA_DEF,
	KD_UP_ALPHA_DEF,
	KD_UP_THETA_DEF,
	KP_DOWN_ALPHA_DEF,
	KD_DOWN_ALPHA_DEF,
	DPOLE_REF,
	REF_GEN_NUM,
	REF_GEN_DEN};
pthread_mutex_t 	mux_parcontr_buffer = PTHREAD_MUTEX_INITIALIZER;	// mutual exclusion per par_control
ref_t ref_buffer = {ALPHA_REF, THETA_REF, SWINGUP_DEF};					// struct riferimento 
pthread_mutex_t 	mux_ref_buffer = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per ref

//----------- Variabili locali

ref_t ref= {ALPHA_REF, THETA_REF, SWINGUP_DEF};
real32_T rtb_rad_to_deg1[2]; // variabile locale che condiene il valore di alpha e theta in gradi.

/* Block signals and states (default storage) */
DW_fast_T fast_DW;
DW_slow_T slow_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_slow_T slow_PrevZCX;


//----------- state_update
void* state_update(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	
	// init
	physics_Init();
	uint16_T rtb_Cast2[2]; 	// da spostare in physics_Init una volta finito
	uint16_T CCR_local;		// da spostare in physics_Init una volta finito
	
	while(!end){
		
		pthread_mutex_lock(&mux_ref_board);
			CCR_local = state_board.CCR;
		pthread_mutex_unlock(&mux_ref_board);
		
		// do stuff
		physics(CCR_local, dn.dist, dn.noise, rtb_Cast2);
		
		pthread_mutex_lock(&mux_ref_board);
			state_board.CNT_alpha = rtb_Cast2[0];
			state_board.CNT_theta = rtb_Cast2[1];
		pthread_mutex_unlock(&mux_ref_board);
		
		// end task
		if(deadline_miss(id)){
			dl_miss_state_update+=1;
		}
		wait_for_period(id);		// wait to next period
	}
	return 0;
}


//---------- control
void* control(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	// init
	//PrevZCX_slow_T slow_PrevZCX;
	//slow_PrevZCX.ref_gen.DiscreteTransferFcn_Reset_ZCE = UNINITIALIZED_ZCSIG;
	par_ctrl = par_control_board;
	controller_Init();
	disturbance_and_noise_Init(&slow_DW.dist);
	

	while(!end){
		
		// stuff
		pthread_mutex_lock(&mux_parcontr_board);
			par_ctrl = par_control_board;
		pthread_mutex_unlock(&mux_parcontr_board);
		
		pthread_mutex_lock(&mux_ref_board);
			ref = ref_board;
		pthread_mutex_unlock(&mux_ref_board);
		
		controller(ref.alpha, ref.swingup, state_board.CNT_alpha,
             state_board.CNT_theta, dn.delay, &ref.theta, rtb_rad_to_deg1,
             &state_pc.voltage, &state_board.CCR);
		
		disturbance_and_noise(dn.kick, &slow_DW.dist, dn.noise);
		dn.dist = slow_DW.dist;
		//state_pc.alpha = rtb_rad_to_deg1[0];
		//state_pc.theta = rtb_rad_to_deg1[1];
		
		// end task
		if(deadline_miss(id)){
			dl_miss_control+=1;
		}
		
		wait_for_period(id);		// wait to next period
	}
	
	return 0;
}

// task di comunicazione pc, scrive ref_pc e par_control_pc su buffer, legge state da buffer
void* compc(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	
	while(!end){
		// scrittura di ref_pc su buffer
		pthread_mutex_lock(&mux_ref_buffer);
			pthread_mutex_lock(&mux_ref_pc);
				ref_buffer = ref_pc;
			pthread_mutex_unlock(&mux_ref_pc);
		pthread_mutex_unlock(&mux_ref_buffer);
		
		// scrittura di par_control_pc su buffer
		pthread_mutex_lock(&mux_parcontr_buffer);
			pthread_mutex_lock(&mux_parcontr_pc);
				par_control_buffer = par_control_pc;
			pthread_mutex_unlock(&mux_parcontr_pc);
		pthread_mutex_unlock(&mux_parcontr_buffer);
		
		// lettura di state_buffer e scrittura state_pc
		pthread_mutex_lock(&mux_state_buffer);
			pthread_mutex_lock(&mux_state_pc);
				state_pc = state_buffer;
			pthread_mutex_unlock(&mux_state_pc);
		pthread_mutex_unlock(&mux_state_buffer);
		
		
		// end task
		if(deadline_miss(id)){
			dl_miss_compc+=1;
		}
		wait_for_period(id);		// wait to next period

	}
	return 0;
}

// task di comunicazione scheda, scrive state su buffer, legge par_control e ref da buffer			DA SISTEMARE!!!!!!!!!!!!!!!!!!!!!!!
void* comboard(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	
	while(!end){
		
		// lettura di ref da buffer, scrittura di ref_board
		pthread_mutex_lock(&mux_ref_buffer);
			pthread_mutex_lock(&mux_ref_board);
				ref_board = ref_buffer;
			pthread_mutex_unlock(&mux_ref_board);
		pthread_mutex_unlock(&mux_ref_buffer);
		
		// lettura di par_control da buffer, scrittura di par_control_pc
		pthread_mutex_lock(&mux_parcontr_buffer);
			pthread_mutex_lock(&mux_parcontr_board);
				par_control_board = par_control_buffer;
			pthread_mutex_unlock(&mux_parcontr_board);
		pthread_mutex_unlock(&mux_parcontr_buffer);
		
		// scrittura di state_board su buffer
		
		
		pthread_mutex_lock(&mux_state_buffer);
			pthread_mutex_lock(&mux_state_board);
				state_buffer.alpha = rtb_rad_to_deg1[0];
				state_buffer.theta = rtb_rad_to_deg1[1];
				state_buffer.voltage = state_board.CCR;			//SISTEMAMI SISTEMAMI
			pthread_mutex_unlock(&mux_state_board);
		pthread_mutex_unlock(&mux_state_buffer);
		
		// end task
		if(deadline_miss(id)){
			dl_miss_comboard+=1;
		}
		wait_for_period(id);		// wait to next period

	}
	return 0;
}

