#include <stdio.h>
#include <math.h>
#include <allegro.h>
#include "gui_init.c"
#include "gui.c"
#include "keys.c"


// MAIN
int main()
{
	gui_init(); //inizializza allegro

	//Def variabili
	float alpha = 0, theta = 0; // Angoli
	float bu = 3;	//boh, variabile a caso
	float alphaold=1, thetaold=1;

	do {

		if( thetaold != theta || alphaold != alpha){
			gui(&alpha, &theta, &bu); //aggiorna grafica
		}
		alphaold=alpha; thetaold=theta;
		keys(&alpha, &theta, &bu); //interazione con la tastiera

	}while (!key[KEY_ESC]);

allegro_exit();
return 0;
}
