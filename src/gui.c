//
// Funzione che aggiorna le scritte, aggiorna l'animazione in funzione di alpha, theta e bu
//

#include <stdio.h>
#include <math.h>
#include <allegro.h>


#define PI 3.14159265

void gui(float *alpha, float *theta, float *bu){

	//
	//Par fissi animazione
	float alpharad, thetarad;	// Porta gli angoli in rad
	alpharad = (*alpha )/180 *PI; thetarad = *theta /180 *PI;

	float cosal, sinal, costh, sinth;	//calcolo una volta sin e cos
	cosal = cos(alpharad); sinal = sin(alpharad);
	costh = cos(thetarad); sinth = sin(thetarad);

	char bustr[30], alphastr[30], thetastr[30];	//stringhe di comunicazione che vengono aggiornate
	float l1 = 100, l2 = 80;	//lunghezze aste

	int colscr = 15, colbck = 0, colmdl = 13, colmdl2 = 5; //colori scritte, background, modello
	int dist = 20;

	//
	// SCRITTE
	// bu
	sprintf(bustr, "bu = %5.2f, a/z +-0.1  ", *bu);
	textout_ex(screen, font, bustr, dist*2, dist*2, colscr, colbck);
	//alpha
	sprintf(alphastr, "alpha = %5.2f, k/l +-5  ", *alpha);
	textout_ex(screen, font, alphastr, dist*2, dist*3, colscr, colbck);
	//theta
	sprintf(thetastr, "theta = %5.2f, i/o +-5  ", *theta);
	textout_ex(screen, font, thetastr, dist*2, dist*4, colscr, colbck);

	//
	// ANIMAZIONE
	int pos0xasso = 876, pos0yasso = 238;	//posizione centrale rettangolo v.asson
	int pos0xlato = 1094, pos0ylato = 675;	//posizione centrale rettangolo v.lato
	int pos0xalto = 658, pos0yalto = 675;	//posizione centrale rettangolo v.alto
	// Reset viste
	rectfill(screen, 441, 50, 1333 -20 -1, 455, colbck);	//cancello vista asson
	rectfill(screen, 878, 490, 1333 -20 -1, 890, colbck);	//cancello vista lato
	rectfill(screen, 445, 490, 874, 890, colbck); 	//cancello vista alto

	// update vettori OA, AP, coordinate "vere"
	float OAx, OAy, APx, APy, APz;
	OAx = l1 * cosal;
	OAy = l1 * sinal;
	//OAz = 0;
	APx = -l2 * sinal * sinth;
	APy = l2 * cosal * sinth;
	APz = l2 * costh;

	// Vista Asson
	int OAxasso, OAyasso, APxasso, APyasso;
	OAxasso = sqrt(2)/2 * (OAy - OAx);
	OAyasso = sqrt(6)/6 * (OAy + OAx);
	APxasso = sqrt(2)/2 * (APy - APx);
	APyasso = sqrt(6)/6 * (APy + APx - 2*APz);
	// APxasso = l2*sin(alpharad + PI/4)*sinth; 							//Verifca con codice prodotto da Matlab
	// APyasso = -(sqrt(6)*l2*(2*costh - cosal*sinth + sinal*sinth))/6;		//Verifca con codice prodotto da Matlab
	line(screen, pos0xasso, pos0yasso + 0.6*l1, pos0xasso, pos0yasso-2, colscr);	//asse verticale ( da disegnare prima )
	line(screen, pos0xasso, pos0yasso, pos0xasso + OAxasso, pos0yasso + OAyasso, colmdl);	// linea OA
	line(screen, pos0xasso + OAxasso, pos0yasso + OAyasso, pos0xasso + OAxasso + APxasso , pos0yasso + OAyasso + APyasso, colmdl2);	// linea AP

	// Vista Lato
	int APxlato, APylato;
	APxlato = l2 * sinth;
	APylato = - APz;
	line(screen, pos0xlato, pos0ylato, pos0xlato + APxlato, pos0ylato + APylato, colmdl2); // linea AP

	// Vista Alto
	int OAxalto, OAyalto, APxalto, APyalto;
	OAxalto = OAy;
	OAyalto = OAx;
	APxalto = APy;
	APyalto = APx;
	line(screen, pos0xalto, pos0yalto, pos0xalto + OAxalto, pos0yalto + OAyalto, colmdl); // linea OA
	line(screen, pos0xalto + OAxalto, pos0yalto + OAyalto, pos0xalto + OAxalto + APxalto, pos0yalto + OAyalto + APyalto, colmdl2);// linea AP

}
