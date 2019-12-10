#include <allegro.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

#include "condiviso.h"
#include "ptask.h"

#include "gui.h"
#include "keys.h"

//----------- Risorse condivise
State state_reset = 
	{ALPHA_0, 
	ALPHADOT_0,
	THETA_0,
	THETADOT_0,
	CURRENT_0,
	VOLTAGE_0,
	CCR_0,
	ENC_ALPHA_0,
	ENC_THETA_0
	};	// struct stato

State state={ALPHA_0, 
	ALPHADOT_0,
	THETA_0,
	THETADOT_0,
	CURRENT_0,
	VOLTAGE_0,
	CCR_0,
	ENC_ALPHA_0,
	ENC_THETA_0
	};	
	
Ref ref = {ALPHA_0, THETA_0};					// struct riferimento 
View view = {LON_0, LAT_0};						// struct vista
Par_control par_control = {KP_ALPHA_DEF, KD_ALPHA_DEF, KP_THETA_DEF, KD_THETA_DEF, KSU_DEF};// struct con parametri del controllore
int end = 0;			// regola chiusura threads
int end_su = 0;			// regola chiusura task state_update
int end_c = 0;			// regola chiusura task control
int brake = 0;			// spegne il motore ma non la scheda

//----------- Mutex per le risorse condivise
pthread_mutex_t 	mux_state = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per state
pthread_mutex_t 	mux_ref = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per ref
pthread_mutex_t 	mux_view = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per view
pthread_mutex_t 	mux_parcontr = PTHREAD_MUTEX_INITIALIZER;		// mutual exclusion per par_control
pthread_mutex_t		mux_buffer = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per buffer


//----------- init 
int init(){
	printf("Caricamento...\n");
	srand(time(NULL));
	
	if (gui_init()) return 1;   
    printf("Grafica inizializzata!\n");
	
    return 0;
}

//----------- exit
int exiting(){
	printf("Chiusura thread...\n");
	wait_for_task_end(ID_KEYS);
	wait_for_task_end(ID_GUI);
	printf("Chiusura Allegro...\n");
	allegro_exit();	
	return 0;
}

// int task_create(void* (*task)(void *), int i, int period, int drel, int prio){
// period = drel (rate monotonic)

//----------- main 
int main()
{    
    init();
	task_create(keys, ID_KEYS, PERIOD_KEYS, PERIOD_KEYS, PRIO_KEYS);				// Interazioni con tastiera (dentro c'e` attivazione state_update e control)
	task_create(gui, ID_STATE_UPDATE, 1000/FPS, 1000/FPS, PRIO_GUI);				// update interfaccia
	exiting();
	
	return 0;
}



END_OF_MAIN()
