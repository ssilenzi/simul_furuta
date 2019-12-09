#include "keys.h"

int state_freeze = 0;
void* keys(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	char ascii, scan;
	while(!end){
		if (keypressed()) {  		// importante altrimenti readkey blocca l'esecuzione
		get_keycodes(&scan, &ascii);
		
		// Create Thread State Update
		if (scan==KEY_A) {
		
			if(!state_freeze){
				end_pc=0;
				task_create(state_update, ID_STATE_UPDATE, PERIOD_STATE_UPDATE, PERIOD_STATE_UPDATE, PRIO_STATE_UPDATE);
				state_freeze=1;
			}
			else{
				end_pc = 1;
				state_freeze = 0;
			}         
		}
        
		// End Threads
		if (scan==KEY_ESC) {
			end_pc=1;
			end = 1;
		}
        
		// reset state
		
		if (scan ==KEY_R) {
			pthread_mutex_lock(&mux_state);
				state.alpha = ALPHA_0;
				state.theta = THETA_0;
			pthread_mutex_unlock(&mux_state);
			pthread_mutex_lock(&mux_ref);
				ref.alpha = ALPHA_0;
				ref.theta = THETA_0;
			pthread_mutex_unlock(&mux_ref);

		}
		
		
		/*
         *      RIFERIMENTO
         */

		// REF_ALPHA a/z
		if (scan==KEY_I) {
			pthread_mutex_lock(&mux_ref);
				ref.alpha += -INCR_ANG;
			pthread_mutex_unlock(&mux_ref);
			
		}
		if (scan==KEY_O) {
			pthread_mutex_lock(&mux_ref);
				ref.alpha += INCR_ANG;
			pthread_mutex_unlock(&mux_ref);
		}
		
		/*
         *      STATO, andra` cancellato
         */
		
		// STATE_ALPHA k/l
		if (scan==KEY_K) {
			pthread_mutex_lock(&mux_state);
				state.alpha += -INCR_ANG;
			pthread_mutex_unlock(&mux_state);
			
		}
		if (scan==KEY_L) {
			pthread_mutex_lock(&mux_state);
				state.alpha += INCR_ANG;
			pthread_mutex_unlock(&mux_state);
			
		}
		// STATE_THETA i/o
		if (scan==KEY_N) {
			pthread_mutex_lock(&mux_state);
				state.theta += -INCR_ANG;
			pthread_mutex_unlock(&mux_state);
		}
		if (scan==KEY_M) {
			pthread_mutex_lock(&mux_state);
				state.theta += INCR_ANG;
			pthread_mutex_unlock(&mux_state);
		}
		
		/*
         *      VIEW
        */ 
        // reset vista
		if (scan==KEY_T) {
			pthread_mutex_lock(&mux_view);
				view.lon = LON_0;
				view.lat = LAT_0;
			pthread_mutex_unlock(&mux_view);
			
		}
        
        //VIEW_LAT up down
		if (scan==KEY_UP) {
			pthread_mutex_lock(&mux_view);
			if (view.lat + INCR_ANG <= LAT_MAX) {
				view.lat += INCR_ANG;
			}
			pthread_mutex_unlock(&mux_view);
			
		}
		if (scan==KEY_DOWN) {
			pthread_mutex_lock(&mux_view);
			if (view.lat + -INCR_ANG >= -LAT_MAX) {
				view.lat += -INCR_ANG;
			}
			pthread_mutex_unlock(&mux_view);

		}
		// VIEW_LON left right
		if (scan==KEY_LEFT) {
			pthread_mutex_lock(&mux_view);
				view.lon += -INCR_ANG;
			pthread_mutex_unlock(&mux_view);			
			
		}
		if (scan==KEY_RIGHT) {
			pthread_mutex_lock(&mux_view);
				view.lon += +INCR_ANG;
			pthread_mutex_unlock(&mux_view);				
			
		}
	} // end keypressed
		wait_for_period(id);			// wait to next period
	}
	return 0;
}


// get_keycodes
void get_keycodes(char *scan, char *ascii)
{
	// The following function waits for a key pressed and extracts
	// the corresponding ASCII code and scan code:
	int k;
	k = readkey(); // block until a key is pressed
	*ascii = k; // get ASCII code
	*scan = k >> 8; // get scan code
}

/*// get_string
void get_string(char *str, int x, int y, int c, int b)
{
	// The following function reads a string from the keyboard and displays
	// the echo in graphic mode at position (x,y), color c and background b:
	char ascii, scan, s[2];
	int i = 0;
	do {
		get_keycodes(&scan, &ascii);
		if (scan != KEY_ENTER) {
			s[0] = ascii; // put ascii in s for echoing
			s[1] = '\0';
			textout_ex(screen, font, s, x, y, c, b); // echo
			x = x + 8;
			str[i++] = ascii; // insert character in string
		}
	} while (scan != KEY_ENTER);

		str[i] = '\0';
}*/
