#include "gui_init.h"

//Static GUI
int gui_init()
{
	// Init allegro
	if (allegro_init() != 0)
		return 1;
	set_color_depth(color_depth); 	// RGB mode (32 bits)
	install_keyboard();		//posso usare la tastiera

	// dimensioni schermo
	//int wscreen = 1024, hscreen = 768;

	// dimensioni dei rettangoli
	//dist = 20; //distanza tra i rettangoli
	int hrett1 = hscreen - 2 * dist; // altezza rettangolo 1
	//int wrett1 = 400;
	int wrett5 = wscreen - 3 * dist - wrett1;
	int hrett3 = wrett5 / 2;
	int wrett3 = wrett5 / 2;
	int hrett4 = hrett3;
	int wrett4 = wrett3;
	//int hrett2 = wrett5 / 2;
	int hrett2 = hscreen - 2 * dist - hrett3;
	int wrett2 = wrett5;
	//int hrett5 = hscreen - 3 * dist - hrett2 - hrett3;

	if (set_gfx_mode(GRAFICA,wscreen,hscreen,0,0) != 0) {	// apre screen
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
		return 1;
	}

	// scelta colori rettangoli, scritte, background
	int colrett;
	colbck = makecol(190, 190, 190);
	colrett = makecol(0, 0, 179);
	colscr = makecol(0, 0, 0);

	// colora background
	clear_to_color(screen, colbck);

	// Disegno rettangoli e cose statiche
	//rett1 - coeff, sinistra
	rect(screen, dist, dist, dist + wrett1, dist + hrett1, colrett);
		char exit[50], reset1[50], reset2[50], reset3[50];
		sprintf(exit, "Premere Esc per uscire");
		textout_ex(screen, font, exit, dist*2, dist*5, colscr, colbck);
		sprintf(reset1, "R per resettare");
		textout_ex(screen, font, reset1, dist*2, dist*6, colscr, colbck);
		sprintf(reset2, "Up, down, left right per modificare la vista");
		textout_ex(screen, font, reset2, dist*2, dist*7, colscr, colbck);
		sprintf(reset3, "T per resettare la vista");
		textout_ex(screen, font, reset3, dist*2, dist*8, colscr, colbck);
	//rett2 - Vista assonometrica
	rect(screen, dist + wrett1 + dist, dist, dist + wrett1 + dist + wrett2 , dist + hrett2, colrett);
		char assostr[50];
		sprintf(assostr, "Vista Assonometrica");
		textout_ex(screen, font, assostr, round( dist + wrett1 + dist  + wrett2 /2 -3.5*dist ), 2 * dist , colscr, colbck);
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
	//rect(screen, dist + wrett1 + dist , dist + hrett2 + hrett3 + dist , dist + wrett1 + dist + wrett5,  dist + hrett2 + hrett3 + dist + hrett5, colrett);
/*		char exit[50], reset[50], resetvis[65];
		sprintf(exit, "Premere Esc per uscire.");
		textout_ex(screen, font, exit, 3*dist + wrett1 , 3*dist + hrett2 + hrett3, colscr, colbck);
		sprintf(reset, "R per resettare.");
		textout_ex(screen, font, reset, 3*dist + wrett1, 4*dist + hrett2 + hrett3, colscr, colbck);
		sprintf(resetvis, "Up, down, left right per modificare e T per resettare la vista.");
		textout_ex(screen, font, resetvis, 15*dist + wrett1, 3*dist + hrett2 + hrett3, colscr, colbck);*/

	// Calcoli per la grafica
	// centri dei disegni
	pos0xasso = wrett1 + wrett2/2 + 2*dist;
	pos0yasso = hrett2/2 + dist;			// posizione centrale rettangolo v.asson
	pos0yasso += dist;						// per fare spazio alla scritta
	pos0xlato = wrett1 + wrett3 + wrett4/2 + 2*dist;
	pos0ylato = hrett2 + hrett3/2 + dist;	// posizione centrale rettangolo v.lato
	pos0ylato += dist;
	pos0xalto = wrett1 + wrett3/2 + 2*dist;
	pos0yalto = hrett2 + hrett3/2 + dist;	// posizione centrale rettangolo v.alto
	pos0yalto += dist;
	// reset viste
	resetasso.x1 = wrett1 + 2*dist + 1;
	resetasso.y1 = dist + 1;
	resetasso.y1 += 2*dist;					// per fare spazio alla scritta
	resetasso.x2 = wrett1 + wrett2 + 2*dist - 1;
	resetasso.y2 = hrett2 + dist - 1;
	resetalto1x = wrett1 + 2*dist + 1;
	resetalto1y = hrett2 + dist + 1;
	resetalto1y += 2*dist;
	resetalto2x = wrett1 + wrett3 + 2*dist - 1;
	resetalto2y = hrett2 + hrett3 + dist - 1;
	resetlato1x = wrett1 + wrett3 + 2*dist + 1;
	resetlato1y = hrett2 + dist + 1;
	resetlato1y += 2*dist;
	resetlato2x = wrett1 + wrett3 + wrett4 + 2*dist - 1;
	resetlato2y = hrett2 + hrett4 + dist - 1;
	// colori modello, rif
	colmdl = makecol(255, 0, 0);
	colmdl2 = makecol(255, 204, 0);
	colrif = makecol(128, 128, 128);

	return 0;
}














