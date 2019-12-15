#include <allegro.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

#include "condiviso.h"
#include "ptask.h"

#include "gui.h"
#include "keys.h"
#include "simulation.h"

//----------- Risorse condivise

/*
 * _pc = variabile su pc
 * _board = variabile sulla scheda simulata
 * _buffer = variabile su buffer
 * 
 */



//state
/*State state_buffer= 
	{ALPHA_0, 
	ALPHADOT_0,
	THETA_0,
	THETADOT_0,
	CURRENT_0,
	VOLTAGE_0,
	CCR_0,
	ENC_ALPHA_0,
	ENC_THETA_0
	}; 			// struct stato
pthread_mutex_t 	mux_state_buffer = PTHREAD_MUTEX_INITIALIZER;
*/

/*State state_board=
	{ALPHA_0, 
	ALPHADOT_0,
	THETA_0,
	THETADOT_0,
	CURRENT_0,
	VOLTAGE_0,
	CCR_0,
	ENC_ALPHA_0,
	ENC_THETA_0
	}; 
pthread_mutex_t 	mux_state_board = PTHREAD_MUTEX_INITIALIZER;
	*/
	
State state_pc=
	{ALPHA_0, 
	ALPHADOT_0,
	THETA_0,
	THETADOT_0,
	CURRENT_0,
	VOLTAGE_0,
	CCR_0,
	ENC_ALPHA_0,
	ENC_THETA_0
	};
pthread_mutex_t 	mux_state_pc = PTHREAD_MUTEX_INITIALIZER;

	
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
	};// struct stato per il reset

	
//par_control
/*Par_control par_control_buffer = 
	{KP_ALPHA_DEF, 
	KD_ALPHA_DEF, 
	KP_THETA_DEF, 
	KD_THETA_DEF, 
	KSU_DEF};	// struct con parametri del controllore
*/
	
Par_control par_control_pc = 
	{KP_ALPHA_DEF, 
	KD_ALPHA_DEF, 
	KP_THETA_DEF, 
	KD_THETA_DEF, 
	KSU_DEF};	// struct con parametri del controllore
pthread_mutex_t 	mux_parcontr_pc = PTHREAD_MUTEX_INITIALIZER;		// mutual exclusion per par_control
/*
Par_control par_control_board = 
	{KP_ALPHA_DEF, 
	KD_ALPHA_DEF, 
	KP_THETA_DEF, 
	KD_THETA_DEF, 
	KSU_DEF};	// struct con parametri del controllore
pthread_mutex_t 	mux_parcontr_board = PTHREAD_MUTEX_INITIALIZER;		// mutual exclusion per par_control
*/

Par_control par_control_reset = 
	{KP_ALPHA_DEF, 
	KD_ALPHA_DEF, 
	KP_THETA_DEF, 
	KD_THETA_DEF, 
	KSU_DEF};	// struct con parmetri del controllore di default

	
int end = 0;			// regola chiusura threads

int brake = 1;			// spegne il motore ma non la scheda consentendo di continuare la lettura degli encoder
pthread_mutex_t		mux_brake = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per brake
	
	
// Variabili solo PC	
Ref ref_pc = {ALPHA_0, THETA_0};		// struct riferimento 
pthread_mutex_t 	mux_ref_pc = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per ref
//Ref ref_board = {ALPHA_0, THETA_0};		// struct riferimento 
//pthread_mutex_t 	mux_ref_board = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per ref

//Ref ref = {ALPHA_0, THETA_0};		// struct riferimento 


View view = {LON_0, LAT_0};			// struct vista





//----------- Mutex per le risorse condivise

pthread_mutex_t 	mux_view = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per view
//pthread_mutex_t		mux_buffer = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per buffer UHMUHMUHM

// Counter deadline miss
int dl_miss_gui = 0;
int dl_miss_keys = 0;
int dl_miss_compc = 0;
int dl_miss_control =0;
int dl_miss_state_update = 0;
int dl_miss_comboard = 0;

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
    init();	//inizializzazione
	
	// creazione dei task
	task_create(state_update, ID_STATE_UPDATE, PERIOD_STATE_UPDATE, PERIOD_STATE_UPDATE, PRIO_STATE_UPDATE); 	// task update dello stato
	
	// task board
	task_create(control, ID_CONTROL, PERIOD_CONTROL, PERIOD_CONTROL, PRIO_CONTROL);								// task controllo
	task_create(comboard, ID_COMBOARD, PERIOD_COMBOARD, PERIOD_COMBOARD, PRIO_COMBOARD);						// task comunicazione dalla scheda su buffer

	// task pc
	task_create(compc, ID_COMPC, PERIOD_COMPC, PERIOD_COMPC, PRIO_COMPC);									// task comunicazione dal pc su buffer
	task_create(keys, ID_KEYS, PERIOD_KEYS, PERIOD_KEYS, PRIO_KEYS);											// Interazioni con tastiera (dentro c'e` attivazione state_update e control)
	task_create(gui, ID_GUI, 1000/FPS, 1000/FPS, PRIO_GUI);														// update interfaccia
	
	
	
	exiting();
	
	return 0;
}



END_OF_MAIN()
