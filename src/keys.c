//
// Funzione che legge i tasti premuti e li assoccia alle rispettive azioni
//

#include <stdio.h>
#include <math.h>
#include <allegro.h>

//get_keycodes
void get_keycodes(char *scan, char *ascii)
{
	//The following function waits for a key pressed and extracts
	//the corresponding ASCII code and scan code:
	int k;
	k = readkey(); // block until a key is pressed
	*ascii = k; // get ASCII code
	*scan = k >> 8; // get scan code
}

// get_string
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
}

void keys(float *alpha, float *theta, float *bu){
	char ascii, scan; // output di get_keycodes(&scan, &ascii)
		if(keypressed() ){  //importante altrimenti readkey blocca l'esecuzione
			get_keycodes(&scan, &ascii);
			//reset
			if(key[KEY_R]){
				*bu = 3.000;
				*alpha = 0;
				*theta = 0;
			}
			//bu a/z
			if(key[KEY_A]) {
				*bu +=  0.1;
			}
			if(key[KEY_Z]){
				*bu += -0.1;
			}
			//alpha i/o
			if(key[KEY_I]) {
				*alpha +=  5;
			}
			if(key[KEY_O]){
				*alpha += -5;
			}
			//alpha k/l
			if(key[KEY_K]) {
				*theta +=  5;
			}
			if(key[KEY_L]){
				*theta += -5;
			}
		} // end keypressed

}
