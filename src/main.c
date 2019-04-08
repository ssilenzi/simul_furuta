#include "main.h"

// MAIN
int main()
{
	if (gui_init() != 0)	// inizializza allegro
		return 1;
	//Variabili
	float alpha = 0, theta = 0; // angoli
	int lon = 45, lat = 35;
	float bu = 3;	// boh, variabile a caso
	float alphaold=1, thetaold=1; // vecchie variabili
	int lonold = 0, latold = 0;

	do {

		if( thetaold != theta || alphaold != alpha || latold != lat || lonold != lon){
			gui(&alpha, &theta, &lon, &lat, &bu); // aggiorna grafica solo se cambia qualcosa
		}
		alphaold=alpha; thetaold=theta; lonold = lon; latold = lat;
		keys(&alpha, &theta, &lon, &lat, &bu); // interazione con la tastiera

		// Soluzione temporanea
		//alpha = ( (int) alpha)%360;
		//theta = ( (int) theta)%360;
		alpha = atan2f(sinf(alpha/180*M_PI), cosf(alpha/180*M_PI))*180/M_PI;
		theta = atan2f(sinf(theta/180*M_PI), cosf(theta/180*M_PI))*180/M_PI;
	} while (!key[KEY_ESC]);

	allegro_exit();
	return 0;
}
END_OF_MAIN()
