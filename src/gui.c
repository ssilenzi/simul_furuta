//
// Funzione che aggiorna le scritte, aggiorna l'animazione in funzione di alpha, theta e bu
//

#include <stdio.h>
#include <math.h>
#include <allegro.h>


#define PI 3.14159265

void gui(float *alpha, float *theta, float *bu){

	//Par fissi animazione
		double alpharad, thetarad; // Porta gli angoli in rad
		char bustr[30], alphastr[30], thetastr[30]; // stringhe di comunicazione che vengono aggiornate
		float l1 = 100, l2 = 80; // lunghezze aste

		int colscr = 15, colbck = 0, colmdl = 13, colmdl2 = 5; // colori
		int dist = 20;


		double OAx, OAy, OAz = 0, APx, APy, APz;


		// SCRITTE
		// bu
		sprintf(bustr, "bu = %5.2f, a/z +-0.1", *bu);
		textout_ex(screen, font, bustr, dist*1.5, dist*2, colscr, colbck);
		//alpha
		sprintf(alphastr, "alpha = %5.2f, i/o +-5", alpha);
		textout_ex(screen, font, alphastr, dist*1.5, dist*3, colscr, colbck);
		//theta
		sprintf(thetastr, "theta = %5.2f, k/l +-5", theta);
		textout_ex(screen, font, thetastr, dist*1.5, dist*4, colscr, colbck);

		// ANIMAZIONE
		// "cancello" vettori vecchi
		// rectfill(screen, x1rett3 +1, y1rett3 +1, x2rett3 -1, y2rett3 -1, colbck); //cancello vista lato
		// rectfill(screen, x1rett4 +1, y1rett4 +1, x2rett4 -1, y2rett4 -1, colbck); //cancello vista alto

		// update vettori OA, AP, OP
		alpharad = *alpha /180 *PI; thetarad = *theta /180 *PI;
		OAx = l1 * cos(alpharad); OAy = l1 * sin(alpharad);
		APx = -l2 * sin(alpharad) * sin(thetarad); APy = -l2 * cos(alpharad) * sin(thetarad); APz = l2 * cos(thetarad);

		//int pos0xlato, pos0ylato, pos0xalto, pos0yalto; //centro pendolo nei due rettangoli
		//pos0xlato = round( ( dist + x2rett3 )/2 ) ; pos0ylato = round( ( y1rett3 + y2rett3 )/2 );
		//pos0xalto = round( ( x1rett4 + x2rett4 )/2 ); pos0yalto = round( ( y1rett4 + y2rett4 )/2 );

		int pos0xlato = 400, pos0ylato = 400;
		int pos0xalto = 600, pos0yalto = 400;
		//	int pos0xlato, pos0ylato, pos0xalto, pos0yalto; //centro pendolo nei due rettangoli
		//pos0xlato = round( ( x1rett3 + x2rett3 )/2 ) ; pos0ylato = round( ( y1rett3 + y2rett3 )/2 );
		//pos0xalto = round( ( x1rett4 + x2rett4 )/2 ); pos0yalto = round( ( y1rett4 + y2rett4 )/2 );

		// Vista Lato
		line(screen, pos0xlato, pos0ylato, pos0xlato + round(OAy), pos0ylato + round(OAz), colmdl); // linea OA
		line(screen, pos0xlato + round(OAy), pos0ylato + round(OAz), pos0xlato + round(OAy+APy), pos0ylato + round(OAz+APz), colmdl2); // linea AP

		// Vista Alto
		line(screen, pos0xalto, pos0yalto, pos0xalto + round(OAy), pos0yalto + round(OAx), colmdl); // linea OA
		line(screen, pos0xalto + round(OAy), pos0yalto + round(OAx), pos0xalto + round(OAy+APy), pos0yalto + round(OAx-APx), colmdl2); // linea AP

}
