#include "physic.h"

//----------- state_update
void* state_update(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	while(!end_pc){
		pthread_mutex_lock(&mux_state);
			state.alpha += 2;
			state.theta += 2;
		pthread_mutex_unlock(&mux_state);
		wait_for_period(id);		// wait to next period
	}
	return 0;
}
