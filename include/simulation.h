#ifndef SIMULATION_H
    #define SIMULATION_H
    
#include <stdio.h>
#include <stdlib.h>
#include <math.h>    
#include "ptask.h"
#include "condiviso.h"



//----------- Task
void* state_update(void* arg); 	// task che updata lo state leggendo ccr

void* control(void* arg);		// task che legge lo stato, il riferimento e setta ccr

void* compc(void* arg);			// task di comunicazione da pc, scrive ref_pc e par_control_pc su buffer, legge state da buffer

void* comboard(void* arg);		// task di comunicazione dalla scheda, scrive su buffer 

#endif //SIMUL_FURUTA_PHYSIC_H
