//
// Funzione che legge i tasti premuti e li assoccia alle rispettive azioni
//

#ifndef SIMUL_FURUTA_KEYS_H
#define SIMUL_FURUTA_KEYS_H

#include <allegro.h>
#include "defines.h"
#include "types.h"

void keys(State *state, Ref *ref, View *view);

// get_keycodes
void get_keycodes(char *scan, char *ascii);

/*// get_string
void get_string(char *str, int x, int y, int c, int b);*/

#endif //SIMUL_FURUTA_KEYS_H
