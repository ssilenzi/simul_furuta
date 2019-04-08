#include "gui.h"

////////////
// GUI
void gui(float *alpha, float *theta, int *lon , int *lat, float *bu){
	// alpha angolo con il link orizzontale (gradi), theta angolo con il link verticale (gradi)
	// lon angolo vista asson longitudinale (gradi), lat angolo vista asson laterale (gradi)

	//--------------------
	char bustr[30], alphastr[30], thetastr[30];					// stringhe di comunicazione che vengono aggiornate
	float thick = 1; 											// spessore linee spesse, non e` in pixel

	//Angoli e grandezze fisiche
	float alpharad, thetarad, lonrad, latrad;					// porta gli angoli in rad
	alpharad = *alpha/180 *M_PI; thetarad = *theta /180 *M_PI;
	lonrad = (float)*lon/180 * M_PI; latrad = (float)*lat/180 * M_PI;
	float cosal, sinal, costh, sinth;							// calcolo sin e cos
	cosal = cos(alpharad); sinal = sin(alpharad);
	costh = cos(thetarad); sinth = sin(thetarad);

	//--------------------
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

	//--------------------
	// ANIMAZIONE
	// Reset viste
	rectfill(screen, resetasso.x1, resetasso.y1, resetasso.x2, resetasso.y2, colbck);	// cancello vista asson
	rectfill(screen, resetlato.x1, resetlato.y1, resetlato.x2, resetlato.y2, colbck);	// cancello vista lato
	rectfill(screen, resetalto.x1, resetalto.y1, resetalto.x2, resetalto.y2, colbck); 	// cancello vista alto

	//--------------------
	// Vista Assonometrica
	int l1 = L1_ASSO, l2 = L2_ASSO;	//lunghezze aste

	TwoPoints riflink1ass, riflink2ass; //riferimenti link vista assonometrica
	riflink1ass.x1 = pos0xasso;
	riflink1ass.y1 = pos0yasso;
	riflink1ass.x2 = pos0xasso - l1*sin(lonrad);
	riflink1ass.y2 = pos0yasso + l1*sin(latrad)*cos(lonrad);
	riflink2ass.x1 = pos0xasso + l1*sin(alpharad - lonrad);
	riflink2ass.y1 = pos0yasso + l1*sin(latrad)*cos(alpharad - lonrad);
	riflink2ass.x2 = pos0xasso + l1*sin(alpharad - lonrad);
	riflink2ass.y2 = pos0yasso + l1*sin(latrad)*cos(alpharad - lonrad) - l2*cos(latrad);

	TwoPoints link1ass, link2ass; //link vista assonometrica
	link1ass.x1 = pos0xasso;
	link1ass.y1 = pos0yasso;
	link1ass.x2 = pos0xasso + l1*sin(alpharad - lonrad);
	link1ass.y2 = pos0yasso + l1*sin(latrad)*cos(alpharad - lonrad);
	link2ass.x1 = pos0xasso + l1*sin(alpharad - lonrad);
	link2ass.y1 = pos0yasso + l1*sin(latrad)*cos(alpharad - lonrad);
	link2ass.x2 = pos0xasso + l1*sin(alpharad - lonrad) + l2*sinth*cos(alpharad - lonrad);
	link2ass.y2 = pos0yasso + l1*sin(latrad)*cos(alpharad - lonrad) -l2*(cos(latrad)*costh - cosal*sin(latrad)*sin(lonrad)*sinth +
			   cos(lonrad)*sinal*sin(latrad)*sinth);

	// Disegno riferimenti
	thick_line(screen, pos0xasso, pos0yasso + l1*cos(latrad), pos0xasso, pos0yasso, thick, makecol(0,0,0));	//asse verticale
	line(screen, riflink1ass.x1, riflink1ass.y1, riflink1ass.x2, riflink1ass.y2, colrif); //rif link1
	line(screen, riflink2ass.x1, riflink2ass.y1, riflink2ass.x2, riflink2ass.y2, colrif); //rif link2
	circlerif_alpha(screen, pos0xasso, pos0yasso, l1, &alpharad, &lonrad, &latrad, colrif); //rif alpha
	circlerif_theta(screen, pos0xasso, pos0yasso, l2, l1, &alpharad, &thetarad, &lonrad, &latrad, colrif); //rif theta
	// Disegno link
	thick_line(screen, link1ass.x1, link1ass.y1, link1ass.x2, link1ass.y2, thick, colmdl); //link1
	thick_line(screen, link2ass.x1, link2ass.y1, link2ass.x2, link2ass.y2, thick, colmdl2); //link2


	//--------------------
	// Vista lato
	l2 = L2_LATO;
	TwoPoints link2lato;
	link2lato.x1 = pos0xlato;
	link2lato.y1 = pos0ylato;
	link2lato.x2 = pos0xlato + l2 * sinth;
	link2lato.y2 = pos0ylato - l2 * costh;
	line(screen, link2lato.x1, link2lato.y1, link2lato.x1, link2lato.y1 -l2, colrif); // rif link lato
	circlerif_parup(screen, pos0xlato, pos0ylato, l2, &thetarad, colrif); // rif angolo theta
	thick_line(screen, link2lato.x1, link2lato.y1, link2lato.x2, link2lato.y2, thick, colmdl2); // link lato

	//--------------------
	// Vista alto
	l1 = L1_ALTO;
	TwoPoints link1alto;
	link1alto.x1 = pos0xalto;
	link1alto.y1 = pos0yalto;
	link1alto.x2 = pos0xalto + l1 * sinal;
	link1alto.y2 = pos0yalto + l1 * cosal;
	line(screen, link1alto.x1, link1alto.y1, link1alto.x1, link1alto.y1 + l1, colrif); // rif link alto
	circlerif_pardown(screen, pos0xalto, pos0yalto, l1, &alpharad, colrif); // rif angolo alpha
	thick_line(screen, link1alto.x1, link1alto.y1, link1alto.x2, link1alto.y2, thick, colmdl); // link alto
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
