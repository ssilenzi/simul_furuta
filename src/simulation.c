#include "simulation.h"


//----------- Variabili extern 
extern Ref ref;

extern Par_control par_control;

extern int end;
extern int brake;
extern int dl_miss_control;
extern int dl_miss_state_update;
extern int dl_miss_comboard;
extern int dl_miss_compc;
//int brake_board=1;
extern int brake;	
extern State state_pc;
extern pthread_mutex_t 		mux_state_pc;			// mutual exclusion for state
//State state_buffer;
//pthread_mutex_t 		mux_state_buffer;			// mutual exclusion for state
//extern pthread_mutex_t 		mux_ref;			// mutual exclusion for ref
//extern pthread_mutex_t 		mux_parcontr;		// mutual exclusion for par_control
extern pthread_mutex_t 		mux_brake;			// mutual exclusion for brake
extern Ref ref_pc;
extern pthread_mutex_t		mux_ref_pc;
extern Par_control par_control_pc;
extern pthread_mutex_t 	mux_parcontr_pc;



//---------------- Variabili Board
//State state_board;
//pthread_mutex_t 	mux_state_board = PTHREAD_MUTEX_INITIALIZER;
State state_board=
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
pthread_mutex_t 	mux_state_board = PTHREAD_MUTEX_INITIALIZER;

//Par_control par_control_board;
//pthread_mutex_t 	mux_par_control_board = PTHREAD_MUTEX_INITIALIZER;
Par_control par_control_board = 
	{KP_ALPHA_DEF, 
	KD_ALPHA_DEF, 
	KP_THETA_DEF, 
	KD_THETA_DEF, 
	KSU_DEF};	// struct con parametri del controllore
pthread_mutex_t 	mux_parcontr_board = PTHREAD_MUTEX_INITIALIZER;		// mutual exclusion per par_control

//Ref ref_board;
//pthread_mutex_t 	mux_ref_board = PTHREAD_MUTEX_INITIALIZER;
Ref ref_board = {ALPHA_0, THETA_0};		// struct riferimento 
pthread_mutex_t 	mux_ref_board = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per ref

//---------- Variabili Buffer

State state_buffer=
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
pthread_mutex_t 	mux_state_buffer = PTHREAD_MUTEX_INITIALIZER;
Par_control par_control_buffer = 
	{KP_ALPHA_DEF, 
	KD_ALPHA_DEF, 
	KP_THETA_DEF, 
	KD_THETA_DEF, 
	KSU_DEF};	// struct con parametri del controllore
pthread_mutex_t 	mux_parcontr_buffer = PTHREAD_MUTEX_INITIALIZER;		// mutual exclusion per par_control
Ref ref_buffer = {ALPHA_0, THETA_0};		// struct riferimento 
pthread_mutex_t 	mux_ref_buffer = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per ref




//----------- state_update
void* state_update(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	while(!end){
		//dummy commands
		pthread_mutex_lock(&mux_state_board);
			state_board.alpha += 0.5;
		pthread_mutex_unlock(&mux_state_board);
		
		
		
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
	
	
	// Semafori da mettere in com board
//	State state_board;
//	Par_control par_control_board;
//	Ref ref_board;

	while(!end){
		
		
		if(brake){
			pthread_mutex_lock(&mux_state_board);
				state_board.voltage = 0;
			pthread_mutex_unlock(&mux_state_board);
			
		}else{
			// do stuff
			
			pthread_mutex_lock(&mux_state_board);
				state_board.voltage += 0.1;
				state_board.theta += -0.25;
			pthread_mutex_unlock(&mux_state_board);

			
			
		}
		
		// end task
		if(deadline_miss(id)){
			dl_miss_control+=1;
		}
		
		wait_for_period(id);		// wait to next period
	}
	
	return 0;
}

// task di comunicazione da pc, scrive ref_pc e par_control_pc su buffer, legge state da buffer
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

// task di comunicazione dalla scheda, SCRIVERE
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
				state_buffer = state_board;
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

