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

	//Variabili
	float alpha = 0, theta = 0; // Angoli
	float lon = 45, lat = 35.26439;
	float bu = 3;	//boh, variabile a caso
	float alphaold=1, thetaold=1, lonold = 0, latold = 0; //vecchie variabili

	do {

		if( thetaold != theta || alphaold != alpha || latold != lat || lonold != lon){
			gui(&alpha, &theta, &lon, &lat, &bu); //aggiorna grafica solo se cambia qualcosa
		}
		alphaold=alpha; thetaold=theta; lonold = lon; latold = lat;
		keys(&alpha, &theta, &lon, &lat, &bu); //interazione con la tastiera

		//soluzione temporanea
		alpha = ( (int) alpha)%360;
		theta = ( (int) theta)%360;

	}while (!key[KEY_ESC]);

allegro_exit();
return 0;
}
