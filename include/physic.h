#ifndef PHYSIC_H
    #define PHYSIC_H

#include "ptask.h"
#include "condiviso.h"

//----------- Variabili extern 
//extern Ref ref; //non serve per ora
extern State state;
//extern View view; //non credo servira` mai, DA CANCELLARE
//extern int end;
extern int end_pc;

extern pthread_mutex_t 		mux_state;			// mutual exclusion for state

    
//----------- Task
void* state_update(void* arg);



#endif //SIMUL_FURUTA_PHYSIC_H
