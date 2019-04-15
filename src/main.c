#include "main.h"
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


	Par par_new;
	Par par_old;
	par_new.alpha = 0; par_new.theta = 0; par_new.lon = 45; par_new.lat = 35; par_new.bu = 3;
	par_old.alpha = 1; par_old.theta = 1; par_old.lon = 1; par_old.lat = 1; par_old.bu = 1;

	do {
		gui(par_old, par_new); // aggiorna grafica solo se cambia qualcosa

		par_old.alpha = par_new.alpha; par_old.theta = par_new.theta; par_old.lon= par_new.lon; par_old.lat= par_new.lat; par_old.bu= par_new.bu;

		keys(&par_new); // interazione con la tastiera

		par_new.alpha = atan2f(sinf(par_new.alpha/180*M_PI), cosf(par_new.alpha/180*M_PI))*180/M_PI;
		par_new.theta = atan2f(sinf(par_new.theta/180*M_PI), cosf(par_new.theta/180*M_PI))*180/M_PI;

	} while (!key[KEY_ESC]);

	allegro_exit();
	return 0;
}
END_OF_MAIN()
