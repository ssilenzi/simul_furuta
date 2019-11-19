//
// Types definition.
//

#ifndef SIMUL_FURUTA_TYPES_H
#define SIMUL_FURUTA_TYPES_H

// types for gui
typedef struct {
    int x;
    int y;
} Point; 

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
} TwoPoints;

typedef struct {
    float x;
    float y;
    float z;
} Vect;

typedef struct {
    float sin;
    float cos;
} AngleSinCos;

typedef struct {
    float alpha;
    float theta;
    float I;
} State;

typedef struct {
    float alpha;
    float theta;
    float Kp;
    float Ki;
    float Kd;
} Ref;

typedef struct {
    int lon;
    int lat;
} View;


// types for handling pthread
#include <stdbool.h>
#include <pthread.h>
    // BRUTTO QUI, pero` comodissimo
    // Alternativamente potremmo mettere la definizione in ptask.h

typedef struct task_par {
	bool 		in_use;		// structure is free or in use
	pthread_mutex_t mtx; 	// lock on the structure
	pthread_t 	tid;		// thread id
	void *		(*behaviour)(void *);	// behaviour code
	void *		data;		// behaviour-specific data
	int 		period; 	// period (ms)
	int 		deadline; 	// relative deadline (ms)
	int 		priority; 	// priority [0,99]
	int 		dl_missed;	// no. of deadline misses
	bool 		stopped;	// thread was ordered to stop
	struct timespec at; 	// next activ. time
	struct timespec dl; 	// abs. deadline
} task_par;




#endif //SIMUL_FURUTA_TYPES_H
