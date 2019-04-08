#include "gui.h"

////////////
// GUI
void gui(float *alpha, float *theta, int *lon , int *lat, float *bu){

	// alpha angolo con il link orizzontale (gradi), theta angolo con il link verticale (gradi)
	// lon angolo vista asson longitudinale (gradi), lat angolo vista asson laterale (gradi)

	// Costanti per disegno

	char bustr[30], alphastr[30], thetastr[30];					// stringhe di comunicazione che vengono aggiornate
	float thick = 1; 											// spessore linee spesse, non e` in pixel

	//Angoli e grandezze fisiche
	float alpharad, thetarad, lonrad, latrad;					// porta gli angoli in rad
	alpharad = *alpha/180 *M_PI; thetarad = *theta /180 *M_PI;
	lonrad = (float)*lon/180 * M_PI; latrad = (float)*lat/180 * M_PI;
	float cosal, sinal, costh, sinth;							// calcolo sin e cos
	cosal = cos(alpharad); sinal = sin(alpharad);
	costh = cos(thetarad); sinth = sin(thetarad);

	// SCRITTE

	// bu
	sprintf(bustr, "bu = %5.2f, a/z +-0.1  ", *bu);
	textout_ex(screen, font, bustr, dist*2, dist*2, colscr, colbck);
	// alpha
	sprintf(alphastr, "alpha = %5.2f, k/l +-5  ", *alpha);
	textout_ex(screen, font, alphastr, dist*2, dist*3, colscr, colbck);
	// theta
	sprintf(thetastr, "theta = %5.2f, i/o +-5  ", *theta);
	textout_ex(screen, font, thetastr, dist*2, dist*4, colscr, colbck);

	// ANIMAZIONE

	// Reset viste
	rectfill(screen, resetasso.x1, resetasso.y1, resetasso.x2, resetasso.y2, colbck);	// cancello vista asson
	rectfill(screen, resetlato1x, resetlato1y, resetlato2x, resetlato2y, colbck);	// cancello vista lato
	rectfill(screen, resetalto1x, resetalto1y, resetalto2x, resetalto2y, colbck); 	// cancello vista alto

/*	// update vettori OA, AP, coordinate "vere"
	float OAx, OAy, APz, APy, APx;
	OAx = l1 * cosal;
	OAy = l1 * sinal;
	OAz = 0;
	APx = -l2 * sinal * sinth;
	APy = l2 * cosal * sinth;
	APz = l2 * costh;*/

	// Vista Assonometrica
	int l1 = 133, l2 = 100;	//lunghezze aste
/*	//ISOMETRICA commentata non si sa mai
		OAxasso = sqrt(2)/2 * (OAy - OAx);
		OAyasso = sqrt(6)/6 * (OAy + OAx);
		APxasso = sqrt(2)/2 * (APy - APx);
		APyasso = sqrt(6)/6 * (APy + APx - 2*APz);*/

	// Riferimenti (da disegnare prima)
	int OAxassorif, OAyassorif, APxassorif, APyassorif;
	OAxassorif = - l1*sin(lonrad);
	OAyassorif = l1*sin(latrad)*cos(lonrad);
	APxassorif = 0;
	APyassorif = - l2*cos(latrad);

	// Link
	int OAxasso, OAyasso, APxasso, APyasso;
	OAxasso = l1*sin(alpharad - lonrad);
	OAyasso = l1*sin(latrad)*cos(alpharad - lonrad);
	APxasso = l2*sinth*cos(alpharad - lonrad);
	APyasso = -l2*(cos(latrad)*costh - cosal*sin(latrad)*sin(lonrad)*sinth +
				   cos(lonrad)*sinal*sin(latrad)*sinth);

	// Disegno riferimenti
	thick_line(screen, pos0xasso, pos0yasso + l1*cos(latrad), pos0xasso, pos0yasso, thick, makecol(0,0,0));	//a sse verticale
	line(screen, pos0xasso, pos0yasso, pos0xasso + OAxassorif, pos0yasso + OAyassorif, colrif);	// linea OA
	line(screen, pos0xasso + OAxasso, pos0yasso + OAyasso, pos0xasso + OAxasso + APxassorif , pos0yasso + OAyasso + APyassorif, colrif);
	circlerif_alpha(screen, pos0xasso, pos0yasso, l1, &alpharad, &lonrad, &latrad, colrif);
	circlerif_theta(screen, pos0xasso, pos0yasso, l2, l1, &alpharad, &thetarad, &lonrad, &latrad, colrif);

	// Disegno link
	thick_line(screen, pos0xasso, pos0yasso, pos0xasso + OAxasso, pos0yasso + OAyasso, thick, colmdl);	// linea OA
	thick_line(screen, pos0xasso + OAxasso, pos0yasso + OAyasso, pos0xasso + OAxasso + APxasso , pos0yasso + OAyasso + APyasso, thick, colmdl2);	// linea AP

	// Vista lato
	l2 = 100;
	int APxlato, APylato, APxlatorif, APylatorif;
	APxlatorif = 0; APylatorif = -l2;
	APxlato = l2 * sinth;
	APylato = - l2 * costh;
	line(screen, pos0xlato, pos0ylato, pos0xlato + APxlatorif, pos0ylato + APylatorif, colrif); // riferimento
	circlerif_parup(screen, pos0xlato, pos0ylato, l2, &thetarad, colrif); // rif angolo theta
	thick_line(screen, pos0xlato, pos0ylato, pos0xlato + APxlato, pos0ylato + APylato, thick, colmdl2); // linea AP

	// Vista alto
	l1 = 100;
	int OAxalto, OAyalto,  OAxaltorif, OAyaltorif; // APxalto, APyalto, APxaltorif, APyaltorif;
	OAxaltorif = 0; OAyaltorif = l1;
	// APxaltorif = 0 ; APyaltorif = 0; //inutile
	OAxalto = l1 * sinal;
	OAyalto = l1 * cosal;
	// APxalto = APy;
	// APyalto = APx;
	// riferimento
	line(screen, pos0xalto, pos0yalto, pos0xalto + OAxaltorif, pos0yalto + OAyaltorif, colrif); // linea OA rif
	// line(screen, pos0xalto + OAxalto, pos0yalto + OAyalto, pos0xalto + OAxalto + 0, pos0yalto + OAyalto + 0, colrif);// linea AP
	circlerif_pardown(screen, pos0xalto, pos0yalto, l1, &alpharad, colrif); // rif angolo alpha
	// link
	thick_line(screen, pos0xalto, pos0yalto, pos0xalto + OAxalto, pos0yalto + OAyalto, thick, colmdl); // linea OA
	// thick_line(screen, pos0xalto + OAxalto, pos0yalto + OAyalto, pos0xalto + OAxalto + APxalto, pos0yalto + OAyalto + APyalto, thick, colmdl2);// linea AP
}

///////////
// ThickLine
void thick_line(BITMAP *bmp, float x, float y, float x_, float y_, float thickness, int color){
	float dx = x - x_;
	float dy = y - y_;
	float d = sqrtf(dx * dx + dy * dy);
	if (!d)
		return;
	int v[4 * 2];

	/* left up */
	v[0] = x - thickness * dy / d;
	v[1] = y + thickness * dx / d;
	/* right up */
	v[2] = x + thickness * dy / d;
	v[3] = y - thickness * dx / d;
	/* right down */
	v[4] = x_ + thickness * dy / d;
	v[5] = y_ - thickness * dx / d;
	/* left down */
	v[6] = x_ - thickness * dy / d;
	v[7] = y_ + thickness * dx / d;

	polygon(bmp, 4, v, color);

}

///////////
// Circle_rifalpha: disegno un arco di circonf in prospettiva per visualizzare alpha
void circlerif_alpha(BITMAP *bmp, int xc, int yc, int r, float *alpharad, float *lonrad, float *latrad, int color){
	// bmp, xc xcentro, yc ycentro, raggio cerchio, alpharad, lonrad angolo long vista asson, latrad " ", color colore

	float anglim = 0, d_ang; // angolo limite
	anglim = *alpharad;
	d_ang = 2*M_PI/1000;
	if(*alpharad < 0){
		d_ang = - d_ang;
	} // end if

	for(float t=0; fabsf(t) < fabsf(anglim); t = t + d_ang){  // mi fermo raggiunto alpharad in un giro disegno 1000 punti.
		float x,y;
		x =  xc -r*sin(*lonrad - t);
		y =  yc + r*cos(*lonrad - t)*sin(*latrad);
		putpixel(bmp, x, y, color);
	} // end for

}
// circlerif_theta: disegna un arco di circonf in prospettiva per visualizzare theta
void circlerif_theta(BITMAP *bmp, int xc, int yc, int r, int l1, float *alpharad, float *thetarad, float *lonrad, float *latrad, int color){
	// bmp, xc xcentro, yc ycentro, raggio cerchio, dimensione link1, alpharad, thetarad, lonrad angolo long vista asson, latrad " ", color colore
	float anglim = 0, d_ang; // angolo limite
	anglim = *thetarad;
	d_ang = 2*M_PI/1000;
	if(*thetarad < 0){
		d_ang = - d_ang;
	} // end if

	for(float t=0; fabsf(t) < fabsf(anglim); t = t + d_ang){  // mi fermo raggiunto thetarad in un giro disegno 1000 punti.
		float x,y;
		x = xc + cos(*lonrad)*(l1*sin(*alpharad) + r*cos(*alpharad)*sin(t)) - sin(*lonrad)*(l1*cos(*alpharad) - r*sin(*alpharad)*sin(t));
		y = yc + cos(*lonrad)*sin(*latrad)*(l1*cos(*alpharad) - r*sin(*alpharad)*sin(t)) - r*cos(*latrad)*cos(t) + sin(*latrad)*sin(*lonrad)*(l1*sin(*alpharad) + r*cos(*alpharad)*sin(t));
		putpixel(bmp, x, y, color);
	} // end for
}
// circlerif_parup: disegna un cerchio parametrico che inizia dalla verticale
void circlerif_parup(BITMAP *bmp, int xc, int yc, int r, float *ang, int color){
	// bmp, xc xcentro, yc ycentro, raggio cerchio, ang angolo a cui fermarsi, color colores
	float anglim = 0, d_ang; // angolo limite
	anglim = *ang;
	d_ang = 2*M_PI/1000;
	if(*ang < 0){
		d_ang = - d_ang;
	} // end if
	for(float t=0; fabsf(t) < fabsf(anglim); t = t + d_ang){  // mi fermo raggiunto ang, in un giro disegno 1000 punti
		float x,y;
		x = xc + r*sin(t);
		y = yc - r*cos(t);
		putpixel(bmp, x, y, color);
	} // end for

}
// circlerif_parup: disegna un cerchio parametrico che inizia dalla verticale
void circlerif_pardown(BITMAP *bmp, int xc, int yc, int r, float *ang, int color){
	// bmp, xc xcentro, yc ycentro, raggio cerchio, ang angolo a cui fermarsi, color colores
	float anglim = 0, d_ang; // angolo limite
	anglim = *ang;
	d_ang = 2*M_PI/1000;
	if(*ang < 0){
		d_ang = - d_ang;
	} // end if
	for(float t=0; fabsf(t) < fabsf(anglim); t = t + d_ang){  // mi fermo raggiunto ang, in un giro disegno 1000 punti
		float x,y;
		x = xc + r*sin(t);
		y = yc + r*cos(t);
		putpixel(bmp, x, y, color);
	} // end for

}