#include "keys.h"
#include <stdio.h>
#include <math.h>

void keys(float *alpha, float *theta, int *lon, int *lat, float *bu){
	char ascii, scan; // output di get_keycodes(&scan, &ascii)
	if( keypressed() ){  // importante altrimenti readkey blocca l'esecuzione
		get_keycodes(&scan, &ascii);
		// reset
		if(key[KEY_R]){
			*bu = 3.000;
			*alpha = 0;
			*theta = 0;
		}
		// reset vista
		if(key[KEY_T]){
			*lon = 45;
			*lat = 35;
		}

		// BU a/z
		if(key[KEY_A]) {
			*bu +=  0.1;
		}
		if(key[KEY_Z]){
			*bu += -0.1;
		}
		// ALPHA k/l
		if(key[KEY_K]) {
			*alpha +=  -5;
		}
		if(key[KEY_L]){
			*alpha += 5;
		}
		// THETA i/o
		if(key[KEY_I]) {
			*theta +=  -5;
		}
		if(key[KEY_O]){
			*theta += 5;
		}
		// LAT up down
		if(key[KEY_UP]){
			if (*lat + 5 <= 90) {
				*lat += 5;
			}
		}
		if(key[KEY_DOWN]){
			if (*lat + -5 >= -90) {
				*lat += -5;
			}
		}
		// LON left right
		if(key[KEY_LEFT]){
			*lon += -5;
		}
		if(key[KEY_RIGHT]){
			*lon += +5;
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
