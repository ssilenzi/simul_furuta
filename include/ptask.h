#ifndef SIMUL_FURUTA_PTHREAD_H
#define SIMUL_FURUTA_PTHREAD_H

#include <pthread.h>

#define MAX_THREADS		256



void init_rt_thread_manager();

int start_thread(
		void *(*func)(void *),  // routine code
		void *args,		// routine args
		int policy,		// scheduling policy
		int prd,		// period (ms)
		int dl,			// relative deadline (ms)
		int prio 		// priority [0,99]
);

int stop_thread(unsigned int id);

int how_many_dl_missed(unsigned int id);

#endif //SIMUL_FURUTA_PTHREAD_H
