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
	float bu = 3.000;	//boh, variabile a caso

	do {
		gui(&alpha, &theta, &bu); //aggiorna grafica
		keys(&alpha, &theta, &bu); //interazione con la tastiera
	}while (!key[KEY_ESC]);

allegro_exit();
return 0;
}
