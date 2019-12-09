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
State state;		// struct stato
Ref ref;			// struct riferimento 
View view;			// struct vista
int end;			// regola chiusura threads
int end_pc;			// regola chiusura task della physic e del controllo

//----------- Mutex per le risorse condivise
pthread_mutex_t 	mux_state = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per state
pthread_mutex_t 	mux_ref = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per ref
pthread_mutex_t 	mux_view = PTHREAD_MUTEX_INITIALIZER;			// mutual exclusion per view

//----------- init 
int init(){
	printf("Caricamento...\n");
	srand(time(NULL));
	

	if (gui_init()) return 1;   
    printf("Grafica inizializzata!\n");
    // inizializzazione dei parametri condivisi
	ref.alpha = ALPHA_0; ref.theta = THETA_0;    
	state.alpha = ALPHA_0; state.theta = THETA_0;
	view.lon = LON_0; view.lat = LAT_0;
    
	end = 0;    // flag per chiusura threads
    return 0;
}


//----------- main 
int main()
{    
    init();
	do {
		gui(state, ref, view);        // Update gui se cambia qualcosa
		keys(&state, &ref, &view);    // Interazioni con tastiera
		//state.alpha = atan2f(sinf(par.alpha/180*M_PI), cosf(par.alpha/180*M_PI))*180/M_PI;
		//state.theta = atan2f(sinf(par.theta/180*M_PI), cosf(par.theta/180*M_PI))*180/M_PI;
	} while (!end);
    
	wait_for_task_end(ID_STATE_UPDATE);
	allegro_exit();
	return 0;
}



END_OF_MAIN()
