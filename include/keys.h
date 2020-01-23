#ifndef KEYS_H
	#define KEYS_H

#include <stdio.h>
#include <math.h>
#include <allegro.h>
#include "ptask.h"
#include "condiviso.h"

//keys
void* keys(void* arg);
void key_action();
void key_par_control();

// get_keycodes
void get_keycodes(char *scan, char *ascii);

#endif //SIMUL_FURUTA_KEYS_H
