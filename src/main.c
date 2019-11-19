#include <allegro.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

#include "types.h"
#include "ptask.h"
#include "defines.h"
#include "gui.h"
#include "keys.h"



// MAIN
int main()
{
    
	srand(time(NULL));
    printf("Caricamento...\n");

    /* */
    init_rt_thread_manager();
    printf("Thread manager inizializzato!\n");
    
    
	if (gui_init()) return 1;

    Ref ref;
	ref.alpha = ALPHA_0; ref.theta = THETA_0;
    State state;
	state.alpha = ALPHA_0; state.theta = THETA_0;
    View view;
	view.lon = LON_0; view.lat = LAT_0;

	do {
		gui(state, ref, view);        // Update gui se cambia qualcosa
        
		keys(&state, &ref, &view);    // Interazioni con tastiera

		//state.alpha = atan2f(sinf(par.alpha/180*M_PI), cosf(par.alpha/180*M_PI))*180/M_PI;
		//state.theta = atan2f(sinf(par.theta/180*M_PI), cosf(par.theta/180*M_PI))*180/M_PI;

	} while (!key[KEY_ESC]);

	allegro_exit();
	return 0;
}


END_OF_MAIN()
