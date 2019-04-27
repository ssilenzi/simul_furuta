#include <allegro.h>
#include "gui.h"
#include "keys.h"
#include "types.h"
#include <stdio.h>
#include <math.h>

// MAIN
int main()
{
	if (gui_init()) return 1;

	State state; Ref ref; View view;
	ref.alpha = ALPHA_0; ref.theta = THETA_0;
	state.alpha = ALPHA_0; state.theta = THETA_0;
	view.lon = LON_0; view.lat = LAT_0;

	do {
		gui(state, ref, view); // aggiorna grafica solo se cambia qualcosa
		keys(&state, &ref, &view); // interazione con la tastiera

		//state.alpha = atan2f(sinf(par.alpha/180*M_PI), cosf(par.alpha/180*M_PI))*180/M_PI;
		//state.theta = atan2f(sinf(par.theta/180*M_PI), cosf(par.theta/180*M_PI))*180/M_PI;

	} while (!key[KEY_ESC]);

	allegro_exit();
	return 0;
}
END_OF_MAIN()
