#ifndef SIMULATION_H
    #define SIMULATION_H
    
#include <stdio.h>
#include <stdlib.h>
#include <math.h>    
#include "ptask.h"
#include "condiviso.h"

//----------- Variabili extern 
extern Ref ref;
extern State state;
extern Par_control par_control;

extern int end;
extern int brake;
extern int dl_miss_control;
extern int dl_miss_state_update;
extern int dl_miss_comboard;
extern int dl_miss_compc;

extern pthread_mutex_t 		mux_state;			// mutual exclusion for state
extern pthread_mutex_t 		mux_ref;			// mutual exclusion for ref
extern pthread_mutex_t 		mux_parcontr;		// mutual exclusion for par_control
extern pthread_mutex_t 		mux_brake;			// mutual exclusion for brake



//----------- Task
void* state_update(void* arg); 	// task che updata lo state leggendo ccr

void* control(void* arg);		// task che legge lo stato, il riferimento e setta ccr

void* compc(void* arg);			// task di comunicazione da pc, scrive ref_pc e par_control_pc su buffer, legge state da buffer

void* comboard(void* arg);		// task di comunicazione dalla scheda, scrive su buffer 

#endif //SIMUL_FURUTA_PHYSIC_H
