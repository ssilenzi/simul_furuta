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

//keys
void* keys(void* arg);

void key_action(char scan);

// get_keycodes
void get_keycodes(char *scan, char *ascii);

/*// get_string
void get_string(char *str, int x, int y, int c, int b);
*/




#endif //SIMUL_FURUTA_KEYS_H
