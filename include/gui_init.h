//
//
//

#ifndef SIMUL_FURUTA_GUI_INIT_H
#define SIMUL_FURUTA_GUI_INIT_H

#include <stdio.h>
#include <math.h>
#include <allegro.h>
#include "defines.h"
#include "types.h"
#include "os.h"

//int dist;
int colscr, colbck;
int pos0xasso, pos0yasso, pos0xlato, pos0ylato, pos0xalto, pos0yalto;
TwoPoints resetasso;
//int resetasso1x, resetasso1y, resetasso2x, resetasso2y;
int resetlato1x, resetlato1y, resetlato2x, resetlato2y;
int resetalto1x, resetalto1y, resetalto2x, resetalto2y;
int colmdl, colmdl2, colrif;

//Static GUI
int gui_init();

#endif //SIMUL_FURUTA_GUI_INIT_H
