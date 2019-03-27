#include <stdio.h>
#include <math.h>
#include <allegro.h>

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

//Static GUI
void gui_init()
{
	int hscreen = 1000, wscreen = 1333; //dimensioni schermo
	int hrett1, wrett1, hrett2, wrett2, hrett3, wrett3, hrett4, wrett4, hrett5, wrett5, dist = 20; //dimensioni rettangoli in pixel
	hrett1 = hscreen - 2 * dist; // altezza rettangolo 1
	wrett1 = 400;
	wrett5 = wscreen - 3 * dist -wrett1;
	hrett2 = wrett5;
	wrett2 = wrett5 / 2;
	hrett3 = hrett2 / 2;
	wrett3 = wrett5 / 2;
	hrett4 = hrett3;
	wrett4 = wrett3;
	hrett5 = hscreen - 3 * dist - hrett2;

	//colori rettangoli, scritte, background, modello
	int colrett = 14, colscr = 15, colbck = 0;

	// Init allegro
	allegro_init(); 	//inizializza Allegro
	install_keyboard();	//posso usare la tastiera
	set_color_depth(8); 	// VGA mode (8 bits)
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,wscreen,hscreen,0,0); // apre screen
	clear_to_color(screen, colbck); // black background

	// Disegno rettangoli e cose statiche

	//rett1 - coeff, sinistra
	rect(screen, dist, dist, dist + wrett1, dist + hrett1, colrett);
 	//rett2 - Vista assonometrica
	rect(screen, dist + wrett1 + dist, dist, dist + wrett1 + dist + wrett2 , dist + hrett2, colrett);
	//rett3 - vista alto
	rect(screen, dist + wrett1 + dist + wrett2 , dist , dist + wrett1 + dist + wrett2 + wrett3, dist+hrett3, colrett);
		char altostr[50];
		sprintf(altostr, "Vista Alto");
		textout_ex(screen, font, altostr, round( (dist + wrett1 + dist + wrett2  +  dist + wrett1 + dist + wrett2 + wrett3 )/2 -1.7*dist ) , 2* dist, colscr, colbck);
	//rett4 - vista Lato
		rect(screen, dist + wrett1 + dist + wrett2 , dist + hrett3 , dist + wrett1 + dist + wrett2 + wrett3, dist+hrett3+hrett4, colrett);
		char latostr[50];
		sprintf(latostr, "Vista Lato");
		textout_ex(screen, font, latostr,  round( (dist + wrett1 + dist + wrett2  +  dist + wrett1 + dist + wrett2 + wrett3 )/2 -1.7*dist )  , dist + hrett3 + dist, colscr, colbck);
	//rett5 val desiderati, basso destra
	rect(screen, dist + wrett1 + dist, dist + hrett2 + dist,  dist + wrett1 + dist + wrett5 , dist + hrett2 + dist + hrett5, colrett);
		char exit[50], reset[50];
		sprintf(exit, "Premere Esc per uscire");
		textout_ex(screen, font, exit, dist + wrett1 + dist + dist , dist + hrett2 + dist + dist, colscr, colbck);
		sprintf(reset, "R per resettare");
		textout_ex(screen, font, reset, dist + wrett1 + dist + dist , dist + hrett2 + dist + dist + dist, colscr, colbck);
}














