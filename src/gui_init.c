#include <stdio.h>
#include <math.h>
#include <allegro.h>

//Static GUI
void gui_init()
{
	int hscreen = 1000, wscreen = 1336; //dimensioni schermo
	//dimensioni rettangoli height and width
	int hrett1, wrett1, hrett2, wrett2, hrett3, wrett3, hrett4, wrett4, hrett5, wrett5, dist = 20; 	hrett1 = hscreen - 2 * dist; // altezza rettangolo 1
	wrett1 = 400;
	wrett5 = wscreen - 3 * dist -wrett1;
	hrett2 = wrett5 / 2;
	wrett2 = wrett5;
	hrett3 = hrett2;
	wrett3 = wrett5 / 2;
	hrett4 = hrett3;
	wrett4 = wrett3+1;
	hrett5 = hscreen - 3 * dist - hrett2 - hrett3;

    // Init allegro
    allegro_init(); 	//inizializza Allegro
    install_keyboard();	//posso usare la tastiera
    set_color_depth(16); 	// VGA mode (8 bits)
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,wscreen,hscreen,0,0); // apre screen

	//colori rettangoli, scritte, background, modello
	int colrett = makecol(255, 0, 0), colscr = makecol(0, 0, 0), colbck = makecol(255, 255, 255);
	clear_to_color(screen, colbck); // black background

	// Disegno rettangoli e cose statiche

	//rett1 - coeff, sinistra
	rect(screen, dist, dist, dist + wrett1, dist + hrett1, colrett);
 	//rett2 - Vista assonometrica
	rect(screen, dist + wrett1 + dist, dist, dist + wrett1 + dist + wrett2 , dist + hrett2, colrett);
		char assostr[50];
		sprintf(assostr, "Vista Assonometrica");
		textout_ex(screen, font, assostr, round( dist + wrett1 + dist  + wrett2 /2 -3.5*dist )  , 2 * dist , colscr, colbck);
	//rett3 - vista alto
	rect(screen, dist + wrett1 + dist , dist + hrett2 ,  dist + wrett1 + dist + wrett3, dist + hrett2 + hrett3, colrett);
		char altostr[50];
		sprintf(altostr, "Vista Alto");
		textout_ex(screen, font, altostr, round( dist + wrett1 + dist  + wrett3 /2 -2.1*dist )  , dist + hrett2 + dist, colscr, colbck);
	//rett4 - vista Lato
	rect(screen, dist + wrett1 + dist + wrett3 , dist + hrett2 , dist + wrett1 + dist + wrett3 + wrett4,  dist + hrett2 + hrett4, colrett);
		char latostr[50];
		sprintf(latostr, "Vista Lato");
		textout_ex(screen, font, latostr,  round( dist + wrett1 + dist + wrett3  +  wrett4/2 -2.1*dist )  , dist + hrett2 + dist, colscr, colbck);
	//rett5 help, basso destra
	rect(screen, dist + wrett1 + dist , dist + hrett2 + hrett3 + dist , dist + wrett1 + dist + wrett5,  dist + hrett2 + hrett3 + dist + hrett5, colrett);
		char exit[50], reset[50], resetvis[65];
		sprintf(exit, "Premere Esc per uscire.");
		textout_ex(screen, font, exit, 3*dist + wrett1 , 3*dist + hrett2 + hrett3, colscr, colbck);
		sprintf(reset, "R per resettare.");
		textout_ex(screen, font, reset, 3*dist + wrett1, 4*dist + hrett2 + hrett3, colscr, colbck);
		sprintf(resetvis, "Up, down, left right per modificare e T per resettare la vista.");
		textout_ex(screen, font, resetvis, 15*dist + wrett1, 3*dist + hrett2 + hrett3, colscr, colbck);

}














