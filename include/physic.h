#ifndef PHYSIC_H
    #define PHYSIC_H
    
#include <stdio.h>
#include <stdlib.h>
#include <math.h>    
#include "ptask.h"
#include "condiviso.h"

//----------- Variabili extern 
extern Ref ref;
extern State state;
//extern View view; //non credo servira` mai, DA CANCELLARE
//extern int end;
extern int end_su;
extern int end_c;
extern Par_control par_control;


extern pthread_mutex_t 		mux_state;			// mutual exclusion for state
extern pthread_mutex_t 		mux_ref;			// mutual exclusion for ref
extern pthread_mutex_t 		mux_parcontr;		// mutual exclusion for par_control
    
//----------- Task
void* state_update(void* arg);

void* control(void* arg);



#endif //SIMUL_FURUTA_PHYSIC_H
