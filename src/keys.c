#include "keys.h"

int state_freeze = 0;

void keys(State *state, Ref *ref, View *view) {
	char ascii, scan; // output di get_keycodes(&scan, &ascii)
	if (keypressed()) {  // importante altrimenti readkey blocca l'esecuzione
		get_keycodes(&scan, &ascii);
		
        // Create Thread State Update
        if (scan==KEY_A) {
        
            if(!state_freeze){
                end_pc=0;
                task_create(state_update, ID_STATE_UPDATE, 20, 20, 1);
                state_freeze=1;
            }
            else{
                 end_pc = 1;
                 state_freeze = 0;
            }
            
            
		}
		if (scan==KEY_A) {
            
        }
        
        // End Threads
        if (scan==KEY_ESC) {
            end_pc=1;
			end = 1;
		}
        
        
        // reset
		if (scan ==KEY_R) {
			ref->alpha = ALPHA_0;
			ref->theta = THETA_0;
            state->alpha = ALPHA_0;
            state->theta = THETA_0;
		}
		
		/*
         *      RIFERIMENTO
         */

		// REF_ALPHA a/z
		if (scan==KEY_I) {
			ref->alpha += -INCR_ANG;
		}
		if (scan==KEY_O) {
			ref->alpha += INCR_ANG;
		}
		
		/*
         *      STATO, andra` cancellato
         */
		
		// STATE_ALPHA k/l
		if (scan==KEY_K) {
			state->alpha += -INCR_ANG;
		}
		if (scan==KEY_L) {
			state->alpha += INCR_ANG;
		}
		// STATE_THETA i/o
		if (scan==KEY_N) {
			state->theta += -INCR_ANG;
		}
		if (scan==KEY_M) {
			state->theta += INCR_ANG;
		}
		
		/*
         *      VIEW
        */ 
        // reset vista
		if (scan==KEY_T) {
			view->lon = LON_0;
			view->lat = LAT_0;
		}
        
        //VIEW_LAT up down
		if (scan==KEY_UP) {
			if (view->lat + INCR_ANG <= LAT_MAX) {
				view->lat += INCR_ANG;
			}
		}
		if (scan==KEY_DOWN) {
			if (view->lat + -INCR_ANG >= -LAT_MAX) {
				view->lat += -INCR_ANG;
			}
		}
		// VIEW_LON left right
		if (scan==KEY_LEFT) {
			view->lon += -INCR_ANG;
		}
		if (scan==KEY_RIGHT) {
			view->lon += +INCR_ANG;
		}
	} // end keypressed
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
