//
// Funzione che aggiorna le scritte, aggiorna l'animazione in funzione di alpha, theta e bu
//

#ifndef SIMUL_FURUTA_GUI_H
#define SIMUL_FURUTA_GUI_H

#include <allegro.h>
#include "defines.h"
#include "os.h"
#include "types.h"


//Static GUI
int gui_init();

// GUI
void gui(Par par_new);

// ThickLine
void thick_line(BITMAP *bmp, float x, float y, float x_, float y_, float thickness, int color);

// Circle_rifalpha: disegno un arco di circonf in prospettiva per visualizzare alpha
void circlerif_alpha(BITMAP *bmp, int xc, int yc, int r, float alpharad, float lonrad, float latrad, int color);

// circlerif_theta: disegna un arco di circonf in prospettiva per visualizzare theta
void circlerif_theta(BITMAP *bmp, int xc, int yc, int r, int l1, float alpharad, float thetarad, float lonrad,
float latrad, int color);

// circlerif_parup: disegna un cerchio parametrico che inizia dalla verticale
void circlerif_parup(BITMAP *bmp, int xc, int yc, int r, float ang, int color);

// proiez_ass proietto coordinate spaziali in coordinate di disegno secondo una proiezione assonometrica
Point proiez_asson(Vect P, AngleSinCos Lon, AngleSinCos Lat);

// disegna griglia in assonometria
void grid(Vect P1, Vect P2, int q, int posx, int posy, AngleSinCos Lon, AngleSinCos Lat, int col);

// disegno le viste
void vista_asson(AngleSinCos Alpha, AngleSinCos Theta, AngleSinCos Lon, AngleSinCos Lat, float alpharad, float thetarad,
        float lonrad, float latrad);
void vista_lato(AngleSinCos Theta, float thetarad);
void vista_alto(AngleSinCos Alpha, float alpharad);


#endif //SIMUL_FURUTA_GUI_H
