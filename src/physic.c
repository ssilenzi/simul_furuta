#include "physic.h"

//----------- state_update
void* state_update(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	while(!end_su){
		//dummy commands
		pthread_mutex_lock(&mux_state);
			state.alpha += 0.5;
			state.theta += 0.5;
		pthread_mutex_unlock(&mux_state);
		
		wait_for_period(id);		// wait to next period
	}
	return 0;
}


//---------- control
void* control(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);

	while(!end_c){
		//dummy commands
		pthread_mutex_lock(&mux_ref);
			ref.theta += 1;
			ref.alpha += 1;
		pthread_mutex_unlock(&mux_ref);

		
		
		wait_for_period(id);		// wait to next period
	}
	return 0;
}

