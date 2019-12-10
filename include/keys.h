//
// Funzioni che leggono i tasti premuti e li assocciano alle rispettive azioni.
//

#ifndef KEYS_H
	#define KEYS_H
#include <stdio.h>
#include <math.h>
#include <allegro.h>
#include "ptask.h"
#include "condiviso.h"
#include "physic.h"

// Variabili extern
extern Ref ref;
extern State state;
extern State state_reset;
extern View view;
extern Par_control par_control;

extern int end;
extern int end_su;
extern int end_c;

extern pthread_mutex_t 		mux_state;			// mutual exclusion for state
extern pthread_mutex_t 		mux_ref;			// mutual exclusion for ref
extern pthread_mutex_t 		mux_view;			// mutual exclusion for view
extern pthread_mutex_t 		mux_parcontr;		// mutual exclusion for par_control




//keys
void* keys(void* arg);

// get_keycodes
void get_keycodes(char *scan, char *ascii);

/*// get_string
void get_string(char *str, int x, int y, int c, int b);
*/




#endif //SIMUL_FURUTA_KEYS_H
