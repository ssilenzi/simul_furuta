//
// Foglioche si occupa di aggiornare le scritte e aggiornare l'animazione in funzione dello stato
//

#ifndef SIMUL_FURUTA_GUI_H
#define SIMUL_FURUTA_GUI_H

#include <stdio.h>
#include <math.h>
#include <allegro.h>

#include "ptask.h"
#include "condiviso.h"
#include "os.h"

// Variabili extern
extern Ref ref;
extern State state;
extern View view;
extern int end;
extern int end_pc;
extern pthread_mutex_t 		mux_state;			// mutual exclusion for state
extern pthread_mutex_t 		mux_ref;			// mutual exclusion for ref
extern pthread_mutex_t 		mux_view;			// mutual exclusion for view


//inizializza gui
int gui_init();

// GUI
void* gui(void* arg);



// FUNZIONI INTERNE
// rad
float rad(float ang);

// ThickLine
void thick_line(BITMAP *bmp, float x, float y, float x_, float y_, float thickness, int color);

// Circle_rifalpha: disegno un arco di circonf in prospettiva per visualizzare alpha
void circlerif_alpha(BITMAP *bmp, Point C, int r, AngleSinCos Lon, AngleSinCos Lat, float alpha, float refalpha,
                     int color);

// circlerif_theta: disegna un arco di circonf in prospettiva per visualizzare theta
void circlerif_theta(BITMAP *bmp, Point C, int r, int l1, AngleSinCos Alpha, AngleSinCos Lon, AngleSinCos Lat,
                     float theta, float reftheta, int color);
// circlerif_parup: disegna un cerchio parametrico che inizia dalla verticale
void circlerif_parup(BITMAP *bmp, Point C, int r, float ang, float refang, int color);

// proiez_ass proietto coordinate spaziali in coordinate di disegno secondo una proiezione assonometrica
Point proiez_asson(Vect P, AngleSinCos Lon, AngleSinCos Lat);

// disegna griglia in assonometria
void grid(Vect P1, Vect P2, int q, int posx, int posy, AngleSinCos Lon, AngleSinCos Lat, int col);

// disegno le viste
void vista_asson(float alpha, float refalpha, float theta, float reftheta, float lon, float lat);
void vista_lato(float theta, float reftheta);
void vista_alto(float alpha, float refalpha);



#endif //SIMUL_FURUTA_GUI_H
