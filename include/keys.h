//
// Funzioni che leggono i tasti premuti e li assocciano alle rispettive azioni.
//

#ifndef SIMUL_FURUTA_KEYS_H
#define SIMUL_FURUTA_KEYS_H
#include <stdio.h>
#include <math.h>
#include <allegro.h>
#include "ptask.h"
#include "condiviso.h"
#include "physic.h"

// Variabili extern
extern Ref ref;
extern State state;
extern View view;
extern int end;
extern int end_pc;
extern pthread_mutex_t 		mux_state;			// mutual exclusion for state
extern pthread_mutex_t 		mux_ref;			// mutual exclusion for ref
extern pthread_mutex_t 		mux_view;			// mutual exclusion for view




//keys
void* keys(void* arg);

// get_keycodes
void get_keycodes(char *scan, char *ascii);

/*// get_string
void get_string(char *str, int x, int y, int c, int b);
*/




#endif //SIMUL_FURUTA_KEYS_H
