/*------------------------------------------------------------------------------------------------------
*	Autori: Francesco Petracci, Simone Silenzi
*	
*	Titolo: Inverted Pendulum
*
*	Descrizione generale e funzionalita`
* 			Il programma simula l'interazione BLABLABLA SCRIVIMI
*		
* 		Task:
* 		PC
* 			- gui BLABLABLA SCRIVIMI
* 			- keys BLABLABLA SCRIVIMI
* 			- compc BLABLABLA SCRIVIMI
* 
* 		Scheda
* 			- control BLABLABLA SCRIVIMI
*			- comboard BLABLABLA SCRIVIMI
* 		Fisica
* 			- state_update BLABLABLA SCRIVIMI
* 
* 	Files:
* 	condiviso.h
* 	gui.c, gui.h
* 	keys.c, keys.h
* 
* 
* 
* 
* 
*--------------------------------------------------------------------------------------------------------------------------*/


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

/*
#include "controller.h"
#include "physics.h"
#include "disturbance_and_noise.h"
*/

//----------- Variabili
/*
 * _pc = variabile su pc
 * _board = variabile su scheda simulata
 * _buffer = variabile su buffer
 * 
 */
/* OLD
State state_pc=
	{ALPHA_0, 
	ALPHADOT_0,
	THETA_0,
	THETADOT_0,
	CURRENT_0,
	VOLTAGE_0,
	CCR_0,
	CNT_ALPHA_0,
	CNT_THETA_0
	};
	*/

state_pc_t state_pc=
{	ALPHA_0,
	THETA_0,
	VOLTAGE_0
}; 
pthread_mutex_t 	mux_state_pc = PTHREAD_MUTEX_INITIALIZER;

/*State state_reset = 
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
*/

	
//----------- par_control
/* OLD
 * Par_control par_control_pc = 
	{KP_ALPHA_DEF, 
	KD_ALPHA_DEF, 
	KP_THETA_DEF, 
	KD_THETA_DEF, 
	KSU_DEF};	// struct con parametri del controllore
pthread_mutex_t 	mux_parcontr_pc = PTHREAD_MUTEX_INITIALIZER;	// mutual exclusion per par_control
Par_control par_control_reset = 
	{KP_ALPHA_DEF, 
	KD_ALPHA_DEF, 
	KP_THETA_DEF, 
	KD_THETA_DEF, 
	KSU_DEF};	// struct con parmetri del controllore di default
	*/
par_ctrl_t par_control_pc =
{KP_UP_ALPHA_DEF,
	KP_UP_THETA_DEF,
	KD_UP_ALPHA_DEF,
	KD_UP_THETA_DEF,
	KP_DOWN_ALPHA_DEF,
	KD_DOWN_ALPHA_DEF,
	DPOLE_REF,
	REF_GEN_NUM,
	REF_GEN_DEN};// struct con parmetri del controllore di default
par_ctrl_t par_control_reset =
{KP_UP_ALPHA_DEF,
	KP_UP_THETA_DEF,
	KD_UP_ALPHA_DEF,
	KD_UP_THETA_DEF,
	KP_DOWN_ALPHA_DEF,
	KD_DOWN_ALPHA_DEF,
	DPOLE_REF,
	REF_GEN_NUM,
	REF_GEN_DEN};
pthread_mutex_t 	mux_parcontr_pc = PTHREAD_MUTEX_INITIALIZER;	// mutual exclusion per par_control

//----------- disturbance and noise
par_dn_t par_dn = {
  DIST_AMP_DEF,
  NOISE_AMP_DEF
} ; // parametri disturbance and noise
dn_t dn= {KICK_DEF, DIST_DEF, NOISE_DEF, DELAY_DEF};
	
//----------- miscellanee
int end = 0;			// regola chiusura threads
//int brake = 1;			// spegne il motore ma non la scheda consentendo di continuare la lettura degli encoder
//pthread_mutex_t		mux_brake = PTHREAD_MUTEX_INITIALIZER;		// mutual exclusion per brake

//int swingup = 0;		// regola il controllore di swingup, swingup = 1 attivo
//pthread_mutex_t		mux_swingup = PTHREAD_MUTEX_INITIALIZER;	// mutual exclusion per swingup

//----------- variabili lato pc	
ref_t ref_pc = {ALPHA_REF, THETA_REF, SWINGUP_DEF};		// struct riferimento 
pthread_mutex_t 	mux_ref_pc = PTHREAD_MUTEX_INITIALIZER;
ref_t ref_reset = {ALPHA_REF, THETA_REF, SWINGUP_DEF};
View view = {LON_0, LAT_0};			// struct vista
pthread_mutex_t 	mux_view = PTHREAD_MUTEX_INITIALIZER;

//----------- counter deadline miss
int dl_miss_gui = 0;
int dl_miss_keys = 0;
int dl_miss_compc = 0;
int dl_miss_control = 0;
int dl_miss_state_update = 0;
int dl_miss_comboard = 0;

//----------- init 
int init(){
	printf("Caricamento...\n");
	srand(time(NULL));

	printf("Inizializzazione grafica...\n");
	if (gui_init()) return 1;   
    return 0;
}



//----------- task_creation
int task_creation(){
	printf("Creazione task...\n");
	// info creazione tasks
	// int task_create(void* (*task)(void *), int i, int period, int drel, int prio){
	// period = drel (rate monotonic)
		
	// task fisica
	task_create(state_update, ID_STATE_UPDATE, PERIOD_STATE_UPDATE, PERIOD_STATE_UPDATE, PRIO_STATE_UPDATE); 	// task update dello stato
	// task board
	task_create(control, ID_CONTROL, PERIOD_CONTROL, PERIOD_CONTROL, PRIO_CONTROL);								// task controllo
	task_create(comboard, ID_COMBOARD, PERIOD_COMBOARD, PERIOD_COMBOARD, PRIO_COMBOARD);						// task comunicazione dalla scheda su buffer
	// task pc
	task_create(compc, ID_COMPC, PERIOD_COMPC, PERIOD_COMPC, PRIO_COMPC);										// task comunicazione dal pc su buffer
	task_create(keys, ID_KEYS, PERIOD_KEYS, PERIOD_KEYS, PRIO_KEYS);											// Interazioni con tastiera
	task_create(gui, ID_GUI, 1000/FPS, 1000/FPS, PRIO_GUI);														// update interfaccia
	printf("Simulazione avviata!\n");

	return 0;
}

//----------- exit
int exiting(){
	wait_for_task_end(ID_GUI);
	printf("Chiusura thread...\n");
	wait_for_task_end(ID_KEYS);
	wait_for_task_end(ID_COMPC);
	wait_for_task_end(ID_COMBOARD);
	wait_for_task_end(ID_CONTROL);
	wait_for_task_end(ID_STATE_UPDATE);
	printf("Chiusura Allegro...\n");
	allegro_exit();	
	return 0;
}

//----------- main 
int main()
{    
    init();	// inizializzazione
	
	task_creation(); // creazione task
	
	exiting(); // chiusura e uscita
	
	return 0;
}



END_OF_MAIN()
