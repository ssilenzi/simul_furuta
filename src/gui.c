//
// Funzione che aggiorna le scritte, aggiorna l'animazione in funzione di alpha, theta e bu
//

#include <stdio.h>
#include <math.h>
#include <allegro.h>


#define PI 3.14159265


void ellisse_par(int *xc, int *yc, float *a, float *b, float *angl1, float *angl2, int *color){
	//xc xcentro, yc ycentro, a semiasse x, b semiasse y, angl angolo di rotazione, color colore
	float A, B, t; //passo di disegno
	int x,y;
	A = *a * cos(*angl1);
	B = *b * sin(*angl1);
	for(t=0; t < 2*PI; t = t + 2*PI/1000){  // mi fermo dopo aver fatto un giro, disegno 1000 punti.
		x =  *xc + ( A * cos(t) );
		y =  *yc + ( B * sin(t) );
		putpixel(screen, x, y, *color);
	} //end for

}


void gui(float *alpha, float *theta, float *lon , float *lat, float *bu){

	//alpha angolo con il link orizzontale (gradi), theta angolo con il link verticale (gradi)
	//lon angolo vista asson longitudinale (gradi), lat angolo vista asson laterale (gradi)

	//
	//Par fissi animazione
	float alpharad, thetarad, lonrad, latrad;	// Porta gli angoli in rad
	alpharad = *alpha/180 *PI; thetarad = *theta /180 *PI;
	lonrad = *lon/180 * PI; latrad = *lat/180 * PI;

	float rifscala = 1.15;

	float cosal, sinal, costh, sinth;	//calcolo sin e cos
	cosal = cos(alpharad); sinal = sin(alpharad);
	costh = cos(thetarad); sinth = sin(thetarad);

	char bustr[30], alphastr[30], thetastr[30];	//stringhe di comunicazione che vengono aggiornate
	float l1 = 100, l2 = 80;	//lunghezze aste

	int colscr = 15, colbck = 0, colmdl = 13, colmdl2 = 5, colrif = 15; //colori scritte, background, modello, rif
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

	// Vista Assonometrica
		//ISOMETRICA commentata non si sa mai
		//OAxasso = sqrt(2)/2 * (OAy - OAx);
		//OAyasso = sqrt(6)/6 * (OAy + OAx);
		//APxasso = sqrt(2)/2 * (APy - APx);
		//APyasso = sqrt(6)/6 * (APy + APx - 2*APz);
	//Riferimenti ( da disegnare prima )
	int OAxassorif, OAyassorif, APxassorif, APyassorif;
	OAxassorif = rifscala * l1*sin( -lonrad);
	OAyassorif = rifscala * l1*sin(latrad)*cos(lonrad);
	APxassorif = 0;
	APyassorif = rifscala * ( -l2*cos(latrad) );
	//Link
	int OAxasso, OAyasso, APxasso, APyasso;
	OAxasso = l1*sin(alpharad - lonrad);
	OAyasso = l1*sin(latrad)*cos(alpharad - lonrad);
	APxasso = l2*sinth*cos(alpharad - lonrad);
	APyasso = -l2*(cos(latrad)*costh - cosal*sin(latrad)*sin(lonrad)*sinth +
				cos(lonrad)*sinal*sin(latrad)*sinth);
	//Disegno Riferimenti
	line(screen, pos0xasso, pos0yasso + 0.6*l1*cos(latrad), pos0xasso, pos0yasso-2, colrif);	//asse verticale
	line(screen, pos0xasso, pos0yasso, pos0xasso + OAxassorif, pos0yasso + OAyassorif, colrif);	// linea OA
	line(screen, pos0xasso + OAxasso, pos0yasso + OAyasso, pos0xasso + OAxasso + APxassorif , pos0yasso + OAyasso + APyassorif, colrif);	// linea AP
	//Disegno Link
	line(screen, pos0xasso, pos0yasso, pos0xasso + OAxasso, pos0yasso + OAyasso, colmdl);	// linea OA
	line(screen, pos0xasso + OAxasso, pos0yasso + OAyasso, pos0xasso + OAxasso + APxasso , pos0yasso + OAyasso + APyasso, colmdl2);	// linea AP

	// Vista Lato
	int APxlato, APylato, APxlatorif, APylatorif;
	APxlatorif = 0; APylatorif = -l2 * rifscala;
	APxlato = l2 * sinth;
	APylato = - APz;
	line(screen, pos0xlato, pos0ylato, pos0xlato + APxlatorif, pos0ylato + APylatorif, colrif); //riferimento
	line(screen, pos0xlato, pos0ylato, pos0xlato + APxlato, pos0ylato + APylato, colmdl2); // linea AP


	// Vista Alto
	int OAxalto, OAyalto, APxalto, APyalto, OAxaltorif, OAyaltorif; //  APxaltorif, APyaltorif;
	OAxaltorif = 0; OAyaltorif = l1 * rifscala;
	// APxaltorif = 0 ; APyaltorif = 0; //inutile
	OAxalto = OAy;
	OAyalto = OAx;
	APxalto = APy;
	APyalto = APx;
	//riferimento
	line(screen, pos0xalto, pos0yalto, pos0xalto + OAxaltorif, pos0yalto + OAyaltorif, colrif); // linea OA rif
	line(screen, pos0xalto + OAxalto, pos0yalto + OAyalto, pos0xalto + OAxalto + 0, pos0yalto + OAyalto + 0, colrif);// linea AP
	//link
	line(screen, pos0xalto, pos0yalto, pos0xalto + OAxalto, pos0yalto + OAyalto, colmdl); // linea OA
	line(screen, pos0xalto + OAxalto, pos0yalto + OAyalto, pos0xalto + OAxalto + APxalto, pos0yalto + OAyalto + APyalto, colmdl2);// linea AP


}
