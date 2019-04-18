#include <allegro.h>
#include "gui.h"
#include "keys.h"
#include "types.h"
#include <stdio.h>
#include <math.h>

// MAIN
int main()
{
	if (gui_init() != 0)	// inizializza allegro
		return 1;
	//Variabili
	//float alpha = 0, theta = 0; // angoli
	//int lon = 45, lat = 35;
	//float bu = 3;	// boh, variabile a caso
	//float alphaold=1, thetaold=1; // vecchie variabili
	//int lonold = 0, latold = 0;

	Par par;
	par.alpha = 0; par.theta = 0; par.lon = 45; par.lat = 35; par.bu = 3;

	do {
		gui(par); // aggiorna grafica solo se cambia qualcosa
		keys(&par); // interazione con la tastiera

		//par.alpha = atan2f(sinf(par.alpha/180*M_PI), cosf(par.alpha/180*M_PI))*180/M_PI;
		//par.theta = atan2f(sinf(par.theta/180*M_PI), cosf(par.theta/180*M_PI))*180/M_PI;

	} while (!key[KEY_ESC]);

	allegro_exit();
	return 0;
}
END_OF_MAIN()
