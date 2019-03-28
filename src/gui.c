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
		alpharad = *alpha /180 *PI; thetarad = *theta /180 *PI;

		char bustr[30], alphastr[30], thetastr[30]; // stringhe di comunicazione che vengono aggiornate
		float l1 = 100, l2 = 80; // lunghezze aste

		int colscr = 15, colbck = 0, colmdl = 13, colmdl2 = 5; // colori
		int dist = 20;

		int pos0xasso = 876, pos0yasso = 238;	// posizione centrale rettangolo v.asson
		int pos0xlato = 1094, pos0ylato = 675;	// posizione centrale rettangolo v.lato
		int pos0xalto = 658, pos0yalto = 675;	// posizione centrale rettangolo v.alto
		double OAx, OAy, APx, APy, APylato, APzlato;

	// SCRITTE
		// bu
		sprintf(bustr, "bu = %5.2f, a/z +-0.1", *bu);
		textout_ex(screen, font, bustr, dist*1.5, dist*2, colscr, colbck);
		//alpha
		sprintf(alphastr, "alpha = %5.2f, i/o +-5", *alpha);
		textout_ex(screen, font, alphastr, dist*1.5, dist*3, colscr, colbck);
		//theta
		sprintf(thetastr, "theta = %5.2f, k/l +-5", *theta);
		textout_ex(screen, font, thetastr, dist*1.5, dist*4, colscr, colbck);

		// ANIMAZIONE
		// "cancello" vettori vecchi, punti degli angoli messi a ghiozzo
		rectfill(screen, 441, 50, 1333 -20 -1, 455, colbck);	//cancello vista asson
		rectfill(screen, 878, 490, 1333 -20 -1, 890, colbck); 	//cancello vista lato
		rectfill(screen, 445, 490, 874, 890, colbck); 	//cancello vista alto

		// update vettori OA, AP
		OAx = l1 * cos(alpharad); OAy = l1 * sin(alpharad);
		APx = -l2 * sin(alpharad) * sin(thetarad); APy = -l2 * cos(alpharad) * sin(thetarad); // APz = l2 * cos(thetarad);
		APylato = l2 * sin(thetarad); APzlato =  l2 * cos(thetarad);

		int OAxasso, OAyasso, APxasso, APyasso;
		OAxasso = l1*sin(alpharad)/sqrt(2) - l1*cos(alpharad)/sqrt(2);
		OAyasso = - l1*cos(alpharad)/sqrt(6) - l1*sin(alpharad)/sqrt(6);
		APxasso = (l1*sin(alpharad) + l2*cos(alpharad)* sin(thetarad))/sqrt(2) - (l1*cos(alpharad) - l2*sin(alpharad)*sin(thetarad))/sqrt(2) - OAxasso;
		APyasso =  sqrt(6)*l2*cos(thetarad)/3 - (l1*cos(alpharad) - l2*sin(alpharad)*sin(thetarad))/sqrt(6) - (l1*sin(alpharad) + l2*cos(alpharad)*sin(thetarad))/sqrt(6) - OAyasso;

		// Vista Asson - DA FARE
		line(screen, pos0xasso, pos0yasso, pos0xasso + OAxasso, pos0yasso + OAyasso, colmdl); // linea OA
		line(screen, pos0xasso + OAxasso, pos0yasso + OAyasso, pos0xasso + OAxasso + APxasso , pos0yasso + OAyasso + APyasso, colmdl2); // linea AP
		line(screen, pos0xasso, pos0yasso + 0.6 * l1, pos0xasso, pos0yasso - 0.6 * l1, colscr); //asse verticale

		// Vista Lato
		line(screen, pos0xlato, pos0ylato, pos0xlato + round(APylato), pos0ylato + round(APzlato), colmdl2); // linea AP

		// Vista Alto
		line(screen, pos0xalto, pos0yalto, pos0xalto + round(OAy), pos0yalto - round(OAx), colmdl); // linea OA
		line(screen, pos0xalto + round(OAy), pos0yalto - round(OAx), pos0xalto + round(OAy + APy), pos0yalto - round(OAx - APx), colmdl2); // linea AP

}




