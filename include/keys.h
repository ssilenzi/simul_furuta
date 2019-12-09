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


//keys
void keys(State *state, Ref *ref, View *view);

// get_keycodes
void get_keycodes(char *scan, char *ascii);

/*// get_string
void get_string(char *str, int x, int y, int c, int b);
*/




#endif //SIMUL_FURUTA_KEYS_H
