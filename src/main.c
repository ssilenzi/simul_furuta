/*------------------------------------------------------------------------------------------------------
*	simul_furuta
*
*	Simulatore del Quanser Rotary Inverted Pendulum
*
*	Autori: Francesco Petracci, Simone Silenzi
*	
*--------------------------------------------------------------------------------------------------------------------------*/


//-----------  include
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

//----------- Variabili usate da piu` task
/*
 * _pc = variabile su pc
 * _board = variabile su scheda simulata
 * _buffer = variabile su buffer
 * 
 */

unsigned int period_ctrl = PERIOD_CONTROL;
pthread_mutex_t mux_period = PTHREAD_MUTEX_INITIALIZER;

state_t state_pc={
	ALPHA_0,
	THETA_0,
	VOLTAGE_0};
pthread_mutex_t mux_state_pc = PTHREAD_MUTEX_INITIALIZER;
state_t state_board={
	ALPHA_0,
	THETA_0,
	VOLTAGE_0};
pthread_mutex_t mux_state_board = PTHREAD_MUTEX_INITIALIZER;

	
//----------- par_control
par_ctrl_t par_ctrl_reset = {
	KP_UP_ALPHA_DEF,
	KP_UP_THETA_DEF,
	KD_UP_ALPHA_DEF,
	KD_UP_THETA_DEF,
	KP_DOWN_ALPHA_DEF,
	KD_DOWN_ALPHA_DEF,
	DPOLE_REF_DEF,
	REF_GEN_NUM_DEF,
	REF_GEN_DEN_DEF};
par_ctrl_t par_ctrl_pc = {
	KP_UP_ALPHA_DEF,
	KP_UP_THETA_DEF,
	KD_UP_ALPHA_DEF,
	KD_UP_THETA_DEF,
	KP_DOWN_ALPHA_DEF,
	KD_DOWN_ALPHA_DEF,
	DPOLE_REF_DEF,
	REF_GEN_NUM_DEF,
	REF_GEN_DEN_DEF};
float pole_ref = POLE_REF_DEF;
pthread_mutex_t mux_par_ctrl_pc = PTHREAD_MUTEX_INITIALIZER;	// mutual exclusion per par_control

//----------- disturbance and noise
par_dn_t par_dn_pc = {
	DIST_AMP_DEF,
  	NOISE_AMP_DEF}; // parametri disturbance and noise
pthread_mutex_t	mux_par_dn = PTHREAD_MUTEX_INITIALIZER;
dn_t dn= {KICK_DEF, DIST_DEF, NOISE_DEF, DELAY_DEF};
pthread_mutex_t	mux_dn = PTHREAD_MUTEX_INITIALIZER;		// mutual exclusion per dn
	
//----------- miscellanee
int end = 0;			// regola chiusura threads

//----------- variabili lato pc	
ref_t ref_pc = {
	ALPHA_REF,
	THETA_REF,
	SWINGUP_DEF};		// struct riferimento 
pthread_mutex_t mux_ref_pc = PTHREAD_MUTEX_INITIALIZER;
view_t view = {
	LON_0,
	LAT_0};			// struct vista
pthread_mutex_t mux_view = PTHREAD_MUTEX_INITIALIZER;

//----------- counter deadline miss
int dl_miss_gui = 0;
int dl_miss_keys = 0;
int dl_miss_compc = 0;
int dl_miss_control = 0;
int dl_miss_state_update = 0;
int dl_miss_comboard = 0;

#ifdef EXTIME
/* ex_time[6]:
	 * state_update 0
	 * control 1
	 * compc 2
	 * comboard 3
	 * gui 4
	 * keys 5
*/
int ex_time[6] = {0};
int wc_extime[6] = {0};
struct timespec monotime_i[6], monotime_f[6];
int ex_cnt[6] = {0};
long ex_sum[6] = {0};
#endif

//----------- init 
int init(){
	printf("Caricamento...\n");
	srand(time(NULL));

	printf("Inizializzazione grafica...\n");
	gui_init();
    return 0;
}

//----------- task_creation
int task_creation(){
	printf("Creazione task...\n");
	// Info creazione tasks
	// int task_create(void* (*task)(void *), int i, int period, int drel, int prio);
	// period = drel
		
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
