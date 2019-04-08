//
// Funzione che legge i tasti premuti e li assoccia alle rispettive azioni
//

#ifndef SIMUL_FURUTA_KEYS_H
#define SIMUL_FURUTA_KEYS_H

#include <allegro.h>

void keys(float *alpha, float *theta, int *lon, int *lat, float *bu);

// get_keycodes
void get_keycodes(char *scan, char *ascii);

/*// get_string
void get_string(char *str, int x, int y, int c, int b);*/

#endif //SIMUL_FURUTA_KEYS_H
