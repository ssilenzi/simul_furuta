#ifndef PTASK_H
	#define PTASK_H

#include <time.h>
#include <sched.h>
#include <pthread.h>

//#define _POSIX_C_SOURCE 199309L		//necessario per CLOCK_MONOTONIC

#define MAX_THREAD	1001
#define MAX_TASK 	1000

struct task_par{				// parametri del task
	int arg;					// task index
	long wcet;					// in microseconds
	unsigned int period;		// in milliseconds
	unsigned int deadline;		// relative (ms)
	unsigned int priority;		// in [0-99]
	unsigned int dmiss;			// # of misses
	struct timespec at;			// next activ time
	struct timespec dl;			// abs deadline
};

struct timespec t;				// time variable

struct task_par tp[MAX_THREAD];   // task parameters
pthread_t tid[MAX_THREAD];        // thread id

// Function declaration
extern int clock_nanosleep();

int task_create(
				void* (*task)(void *), 		// function as void pointer
				int i,						// index to identify the task
				int period,					// period of task (ms)
				int drel,					// relative deadline (ms)
				int prio					// priority [0-99]
				);

int get_task_index(void* arg);				// return task index

void set_activation(int i);					// set startup time for period and deadlines

int deadline_miss(int i);					// return 1 if deadline missed

void wait_for_period(int i);				// thread sleeps untill next period bein

void wait_for_task_end(int i);				// wait untill task i terminate his execution

unsigned int task_period(int i);			// return task period

// time variables management
void time_copy(	struct timespec 	*td,
				struct timespec 	ts);

void time_add_ms(struct timespec *t, int ms);

int time_cmp(	struct timespec t1,
				struct timespec t2);

long time_dist(	struct timespec *t1, 		// return time distance in nanoseconds, negative if t2<t1
				struct timespec *t2);

int cpu_set(int cpu);
	
#endif
