//
// Funzione che aggiorna le scritte, aggiorna l'animazione in funzione di alpha, theta e bu
//

#ifndef SIMUL_FURUTA_GUI_H
#define SIMUL_FURUTA_GUI_H

#include <stdio.h>
#include <math.h>
#include <allegro.h>
#include "defines.h"
#include "shared.h"
#include "types.h"

// GUI
void gui(float *alpha, float *theta, int *lon , int *lat, float *bu);

// ThickLine
void thick_line(BITMAP *bmp, float x, float y, float x_, float y_, float thickness, int color);

// Circle_rifalpha: disegno un arco di circonf in prospettiva per visualizzare alpha
void circlerif_alpha(BITMAP *bmp, int xc, int yc, int r, float *alpharad, float *lonrad, float *latrad, int color);

// circlerif_theta: disegna un arco di circonf in prospettiva per visualizzare theta
void circlerif_theta(BITMAP *bmp, int xc, int yc, int r, int l1, float *alpharad, float *thetarad, float *lonrad, \
float *latrad, int color);

// circlerif_parup: disegna un cerchio parametrico che inizia dalla verticale
void circlerif_parup(BITMAP *bmp, int xc, int yc, int r, float *ang, int color);

// circlerif_parup: disegna un cerchio parametrico che inizia dalla verticale
void circlerif_pardown(BITMAP *bmp, int xc, int yc, int r, float *ang, int color);

#endif //SIMUL_FURUTA_GUI_H
