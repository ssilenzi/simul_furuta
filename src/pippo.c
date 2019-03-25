// Pepo e` allegro

#include <stdio.h>
#include <math.h>
#include <allegro.h>

#define PI 3.14159265

//get_keycodes
void get_keycodes(char *scan, char *ascii)
{
	//The following function waits for a key pressed and extracts
	//the corresponding ascii code and scan code:
	int k;
	k = readkey(); // block until a key is pressed
	*ascii = k; // get ascii code
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


// MAIN
int main()
{
	// Init allegro
	allegro_init(); 	//inizializza Allegro
	install_keyboard();	//posso usare la tastiera
	set_color_depth(8); 	// VGA mode (8 bits)
	int hscreen = 600, wscreen = 800; //dimensioni schermo
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,wscreen,hscreen,0,0); // apre screen
	int colrett = 14, colscr = 15, colbck = 0, colmdl = 13, colmdl2 = 5; //colori rettangoli, scritte, background, modello


	// Disegno rettangoli e cose statiche
	int hrett1 = 350, wrett1 = 200, wrett2 = 540, hrett2 = 190, dist = 20; //dimensioni rettangoli in pixel
	clear_to_color(screen, colbck); // black background	
	//rett1 coeff, alto sinistra
	int x1rett1 = dist, 		y1rett1 = dist, 		x2rett1 = x1rett1+wrett1, 	y2rett1 = y1rett1+hrett1;
	rect(screen, x1rett1, y1rett1, x2rett1, y2rett1, colrett);
 
	//rett reset/bottoni, basso sinistra
	int x1rett2 = dist, 		y1rett2 = y2rett1 + dist, 	x2rett2 = x1rett2+wrett1, 	y2rett2 = hscreen-dist;
	rect(screen, x1rett2, y1rett2, x2rett2, y2rett2, colrett); 

	//rett vista lato
	int x1rett3 = x2rett1 +dist, 	y1rett3 = dist,    	 	x2rett3 = x1rett3 + wrett2/2, 	y2rett3 = y1rett3+hrett1;
	rect(screen, x1rett3, y1rett3, x2rett3, y2rett3, colrett);
		char latostr[50];
		sprintf(latostr, "Vista Lato");
		textout_ex(screen, font, latostr, round( ( x1rett3 + x2rett3 )/2 -1.7*dist ) , y1rett3 + dist, colscr, colbck);
	
	//rett vista alto
	int x1rett4 = x2rett3, 		y1rett4 = dist,    	 	x2rett4 = x1rett4 + wrett2/2, 	y2rett4 = y1rett4+hrett1;
	rect(screen, x1rett4, y1rett4, x2rett4, y2rett4, colrett);
		char altostr[50];
		sprintf(altostr, "Vista Alto");
		textout_ex(screen, font, altostr, round( ( x1rett4 + x2rett4 )/2 -1.7*dist ) , y1rett4 + dist, colscr, colbck);

	//rett val desiderati, basso destra
	int x1rett5 = x2rett2+dist, 	y1rett5 = y2rett3+dist,    	x2rett5 = x1rett5+wrett2, 	y2rett5 = y1rett5+hrett2;
	rect(screen, x1rett5, y1rett5, x2rett5, y2rett5, colrett);
		char exit[50], reset[50];
		sprintf(exit, "Premere Esc per uscire");
		textout_ex(screen, font, exit, x2rett5-wrett2/2.8 , y2rett5-dist, colscr, colbck);
		sprintf(reset, "R per resettare");
		textout_ex(screen, font, reset, x2rett5-wrett2/2.8 , y2rett5-2*dist, colscr, colbck);

	//Par fissi animazione
	float bu =3.000;
	float alpha = 0, theta = 0; // Angoli
	double alpharad, thetarad; // Porta gli angoli in rad
	char bustr[30], alphastr[30], thetastr[30]; // stringhe di comunicazione che vengono aggiornate
	char ascii, scan; // output di get_keycodes(&scan, &ascii)
	float l1 = 100, l2 = 80; // lunghezze aste
	int pos0xlato, pos0ylato, pos0xalto, pos0yalto; //centro pendolo nei due rettangoli
	pos0xlato = round( ( x1rett3 + x2rett3 )/2 ) ; pos0ylato = round( ( y1rett3 + y2rett3 )/2 );
	pos0xalto = round( ( x1rett4 + x2rett4 )/2 ); pos0yalto = round( ( y1rett4 + y2rett4 )/2 );
	double OAx, OAy, OAz = 0, APx, APy, APz, OPx, OPy, OPz;
	
	// Update parameters/variables
	do {
	// SCRITTE
	// bu
	sprintf(bustr, "bu = %5.2f, a/z +-0.1", bu);
	textout_ex(screen, font, bustr, dist*1.5, dist*2, colscr, colbck);
	//alpha
	sprintf(alphastr, "alpha = %5.2f, i/o +-5", alpha);
	textout_ex(screen, font, alphastr, dist*1.5, dist*3, colscr, colbck);
	//theta
	sprintf(thetastr, "theta = %5.2f, k/l +-5", theta);
	textout_ex(screen, font, thetastr, dist*1.5, dist*4, colscr, colbck);
	
	// ANIMAZIONE

	// "cancello" vettori vecchi
	rectfill(screen, x1rett3 +1, y1rett3 +1, x2rett3 -1, y2rett3 -1, colbck); //cancello vista lato
	rectfill(screen, x1rett4 +1, y1rett4 +1, x2rett4 -1, y2rett4 -1, colbck); //cancello vista alto
	
	// update vettori OA, AP, OP
	alpharad = alpha/180 *PI; thetarad = theta/180 *PI;
	OAx = l1 * cos(alpharad); OAy = l1 * sin(alpharad);
	APx = -l2 * sin(alpharad) * sin(thetarad); APy = -l2 * cos(alpharad) * sin(thetarad); APz = l2 * cos(thetarad);
	OPx = OAx + APx; OPy = OAy + APy; OPz = APz;

	// Vista Lato
	line(screen, pos0xlato, pos0ylato, pos0xlato + round(OAy), pos0ylato + round(OAz), colmdl); // linea OA
	line(screen, pos0xlato + round(OAy), pos0ylato + round(OAz), pos0xlato + round(OAy+APy), pos0ylato + round(OAz+APz), colmdl2); // linea AP
	
	// Vista Alto
	line(screen, pos0xalto, pos0yalto, pos0xalto + round(OAy), pos0yalto + round(OAx), colmdl); // linea OA
	line(screen, pos0xalto + round(OAy), pos0yalto + round(OAx), pos0xalto + round(OAy+APy), pos0yalto + round(OAx-APx), colmdl2); // linea AP
	


	if(keypressed){  //importante altrimenti readkey blocca l'esecuzione
		get_keycodes(&scan, &ascii);
		//reset
		if(key[KEY_R]){
			bu = 3.000;
			alpha = 0;
			theta = 0;
		}		
		//bu a/z
		if(key[KEY_A]) {
			bu +=  0.1;			
		} 
		if(key[KEY_Z]){
			bu += -0.1;
		}		
		//alpha i/o
		if(key[KEY_I]) {
			alpha +=  5;			
		} 
		if(key[KEY_O]){
			alpha += -5;
		}
		//alpha k/l
		if(key[KEY_K]) {
			theta +=  5;			
		} 
		if(key[KEY_L]){
			theta += -5;
		}


		} // end keypressed
	}while (!key[KEY_ESC]);
	allegro_exit();
	return 0;
}










