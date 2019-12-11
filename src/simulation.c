#include "simulation.h"

//----------- state_update
void* state_update(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	while(!end){
		//dummy commands
		pthread_mutex_lock(&mux_state);
			state.alpha += 0.5;
			state.theta += 0.5;
		pthread_mutex_unlock(&mux_state);
		
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
	State state_board;
	Par_control par_control_board;
	Ref ref_board;
	int brake_board=1;
	
	while(!end){
		
		pthread_mutex_lock(&mux_state);
			state_board = state;			// SPOSTAMI IN COM_BOARD!
		pthread_mutex_unlock(&mux_state);
		pthread_mutex_lock(&mux_parcontr);
			par_control_board = par_control;
		pthread_mutex_unlock(&mux_parcontr);
		pthread_mutex_lock(&mux_ref);
			ref_board = ref;
		pthread_mutex_unlock(&mux_ref);
		pthread_mutex_lock(&mux_brake);
			brake_board = brake;
		pthread_mutex_unlock(&mux_brake);
		
		
		
		if(brake_board){
			state_board.voltage = 0;
		}else{
			// do stuff
			
			state_board.voltage += 0.1;
			ref_board.alpha += 0.1;
			par_control_board.alpha_kd += 0.1;
			
		}

		
		// ricopio var locali in quelle glob
		pthread_mutex_lock(&mux_state);
			state = state_board;			// SPOSTAMI IN COM_BOARD!
		pthread_mutex_unlock(&mux_state);
		
		pthread_mutex_lock(&mux_parcontr);
			par_control = par_control_board;
		pthread_mutex_unlock(&mux_parcontr);
		
		pthread_mutex_lock(&mux_ref);
			ref = ref_board;
		pthread_mutex_unlock(&mux_ref);
		
		if(deadline_miss(id)){
			dl_miss_control+=1;
		}
		
		wait_for_period(id);		// wait to next period
	}
	
	return 0;
}


void* compc(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	
	while(!end){
		
		
		if(deadline_miss(id)){
			dl_miss_compc+=1;
		}
		wait_for_period(id);		// wait to next period

	}
	return 0;
}


void* comboard(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	
	while(!end){
		
		
		if(deadline_miss(id)){
			dl_miss_comboard+=1;
		}
		wait_for_period(id);		// wait to next period

	}
	return 0;
}

