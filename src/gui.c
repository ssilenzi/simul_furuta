#include "gui.h"
#include <stdio.h>
#include <math.h>

static BITMAP *scrbuf;
static Point asson0, lato0, alto0; //centro rettangoli
static TwoPoints resetasson, resetlato, resetalto; //angoli dell'area da resettare prima di disegnare di nuovo
static struct {
	int mdl;	//colore modello
	int mdl2;	//colore modello2
	int vert;	//colore asta verticale
	int rif;	//colore riferimento
	int scr;	//colore scritte
	int bck;	//colore background
	int rett;	//colore rettangoli
} col; //struttura con i colori

static struct{
	int x;
	int y[(int)(hscreen/dist - 2)];
} scritte; // array per scrivere "parametricamente" le scritte

// init gui
int gui_init()
{
	// Init allegro
	if (allegro_init() != 0)
		return 1;
	set_color_depth(color_depth); 	// RGB mode (32 bits)
	install_keyboard();		//posso usare la tastiera

	// dimensioni dei rettangoli
	int hrett1 = hscreen - 2 * dist; // altezza rettangolo 1
	//int wrett1 = 400;
	int wrett5 = wscreen - 3 * dist - wrett1;
	int hrett3 = wrett5 / 2;
	int wrett3 = wrett5 / 2;
	int hrett4 = hrett3;
	int wrett4 = wrett3;
	int hrett2 = hscreen - 2 * dist - hrett3;
	int wrett2 = wrett5;

	int qdistvert = (hscreen)/ dist - 2; // quante dist entrano dentro il mio schermo, dimensione dell'array scritte
	scritte.x = 2*dist;
	for (int i = 0; i < qdistvert; i++) {
		scritte.y[i] = dist * (i+1);
	} //popolo l'array scritte con le posizioni xy delle scritte

	if (set_gfx_mode(GRAFICA,wscreen,hscreen,0,0) != 0) {
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
		return 1;
	}

	scrbuf = create_bitmap(SCREEN_W, SCREEN_H);
	if (!scrbuf) {
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Unable to initialize page flipping\n%s\n", allegro_error);
		return 1;
	}

	// scelta colori rettangoli, scritte, background
	col.bck = COL_BCK;
	col.rett = COL_RETT;
	col.scr = COL_SCR;
	// colori modello, rif
	col.mdl = COL_MDL;
	col.mdl2 = COL_MDL2;
	col.vert = COL_VERT;
	col.rif = COL_RIF;

	// colora background
	clear_to_color(scrbuf, col.bck);

	// Disegno rettangoli e cose statiche
	//rett1 - coeff, sinistra
	rect(scrbuf, dist, dist, dist + wrett1, dist + hrett1, col.rett);
	char exit[50], reset1[50], reset2[50], reset3[50];
	sprintf(exit, "Premere Esc per uscire");
	textout_ex(scrbuf, font, exit, scritte.x, scritte.y[qdistvert-1], col.scr, col.bck);

	sprintf(reset1, "R per resettare");
	textout_ex(scrbuf, font, reset1, scritte.x, scritte.y[qdistvert-2], col.scr, col.bck);

	sprintf(reset2, "Up, down, left right per modificare la vista");
	textout_ex(scrbuf, font, reset2, scritte.x, scritte.y[qdistvert-3], col.scr, col.bck);

	sprintf(reset3, "T per resettare la vista");
	textout_ex(scrbuf, font, reset3, scritte.x, scritte.y[qdistvert-4], col.scr, col.bck);

	//rett2 - Vista assonometrica
	rect(scrbuf, dist + wrett1 + dist, dist, dist + wrett1 + dist + wrett2, dist + hrett2, col.rett);
	char assonstr[50];
	sprintf(assonstr, "Vista Assonometrica");
	textout_ex(scrbuf, font, assonstr, (int)(dist + wrett1 + dist + wrett2 /2 -3.5*dist), 2*dist, col.scr, col.bck);
	//rett3 - vista alto
	rect(scrbuf, dist + wrett1 + dist, dist + hrett2, dist + wrett1 + dist + wrett3, dist + hrett2 + hrett3, col.rett);
	char altostr[50];
	sprintf(altostr, "Vista Alto");
	textout_ex(scrbuf, font, altostr, (int)(dist + wrett1 + dist + wrett3 /2 -2.1*dist), dist + hrett2 + dist,
			col.scr, col.bck);
	//rett4 - vista Lato
	rect(scrbuf, dist + wrett1 + dist + wrett3, dist + hrett2, dist + wrett1 + dist + wrett3 + wrett4,
			dist + hrett2 + hrett4, col.rett);
	char latostr[50];
	sprintf(latostr, "Vista Lato");
	textout_ex(scrbuf, font, latostr, (int)(dist + wrett1 + dist + wrett3 + wrett4/2 -2.1*dist),
			dist + hrett2 + dist, col.scr, col.bck);

	//----------------------------------
	// Calcoli per la grafica
	// posizione centrale rettangolo v.assonometrica
	asson0.x = wrett1 + wrett2/2 + 2*dist;
	asson0.y = hrett2/2 + dist; // posizione centrale rettangolo v.asson
	//asson0.y += dist; // per fare spazio alla scritta
	// posizione centrale rettangolo v.lato
	lato0.x = wrett1 + wrett3 + wrett4/2 + 2*dist;
	lato0.y = hrett2 + hrett3/2 + dist;
	lato0.y += dist;
	// posizione centrale rettangolo v.alto
	alto0.x = wrett1 + wrett3/2 + 2*dist;
	alto0.y = hrett2 + hrett3/2 + dist;
	alto0.y += dist;
	// reset viste
	resetasson.x1 = wrett1 + 2*dist + 1;
	resetasson.y1 = dist + 1;
	resetasson.y1 += 2*dist;
	resetasson.x2 = wrett1 + wrett2 + 2*dist - 1;
	resetasson.y2 = hrett2 + dist - 1;
	resetalto.x1 = wrett1 + 2*dist + 1;
	resetalto.y1 = hrett2 + dist + 1;
	resetalto.y1 += 2*dist;
	resetalto.x2 = wrett1 + wrett3 + 2*dist - 1;
	resetalto.y2 = hrett2 + hrett3 + dist - 1;
	resetlato.x1 = wrett1 + wrett3 + 2*dist + 1;
	resetlato.y1 = hrett2 + dist + 1;
	resetlato.y1 += 2*dist;
	resetlato.x2 = wrett1 + wrett3 + wrett4 + 2*dist - 1;
	resetlato.y2 = hrett2 + hrett4 + dist - 1;

	return 0;
}

// GUI
void gui(Par par_new) {
	static Par par_old = {1, 1, 1, 1, 1};
	char bustr[30], alphastr[30], thetastr[30];	// stringhe di comunicazione che vengono aggiornate
	float alpharad, thetarad, latrad, lonrad;
	AngleSinCos Alpha, Theta, Lon, Lat;

	alpharad = par_new.alpha/180 * M_PI; // conversione in radianti degli angoli nuovi
	thetarad = par_new.theta/180 * M_PI;
	lonrad = par_new.lon/180 * M_PI;
	latrad = par_new.lat/180 * M_PI;

	// ANIMAZIONE
	if (par_new.alpha != par_old.alpha) {

		Alpha.sin = sinf(alpharad);	Alpha.cos = cosf(alpharad);
		vista_alto(Alpha, alpharad);
	}

	if (par_new.theta != par_old.theta) {

		Theta.sin = sinf(thetarad);	Theta.cos = cosf(thetarad);
		vista_lato(Theta, thetarad);
	}

	if (par_new.alpha != par_old.alpha || par_new.theta != par_old.theta || par_new.lon != par_old.lon ||
		par_new.lat != par_old.lat) {

		Alpha.sin = sinf(alpharad);	Alpha.cos = cosf(alpharad);
		Theta.sin = sinf(thetarad);	Theta.cos = cosf(thetarad);
		Lat.sin = sinf(latrad); Lat.cos = cosf(latrad);
		Lon.sin = sinf(lonrad); Lon.cos = cosf(lonrad);
		vista_asson(Alpha, Theta, Lon, Lat, alpharad, thetarad, lonrad, latrad);
	}

	// SCRITTE
	if (par_new.alpha != par_old.alpha || par_new.theta != par_old.theta || par_new.lon != par_old.lon ||
		par_new.lat != par_old.lat || par_new.bu != par_old.bu) {

		// bu
		sprintf(bustr, "bu = %5.2f, a/z +-0.1          ", par_new.bu);
		textout_ex(scrbuf, font, bustr, scritte.x, scritte.y[1], col.scr, col.bck);
		// alpha
		sprintf(alphastr, "alpha = %5.2f, k/l +-5          ", par_new.alpha);
		textout_ex(scrbuf, font, alphastr, scritte.x, scritte.y[2], col.scr, col.bck);
		// theta
		sprintf(thetastr, "theta = %5.2f, i/o +-5          ", par_new.theta);
		textout_ex(scrbuf, font, thetastr,scritte.x, scritte.y[3], col.scr, col.bck);
	}
	blit(scrbuf, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	par_old = par_new;
}

// ThickLine
void thick_line(BITMAP *bmp, float x, float y, float x_, float y_, float thickness, int color) {
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
// Circle_rifalpha: disegno un arco di circonf in prospettiva per visualizzare alpha
void circlerif_alpha(BITMAP *bmp, int xc, int yc, int r, float alpharad, float lonrad, float latrad, int color) {
	// bmp, xc xcentro, yc ycentro, raggio cerchio, alpharad, lonrad angolo long vista asson, latrad " ", color colore

	float anglim = 0, d_ang; // angolo limite
	anglim = alpharad;
	d_ang = 2*M_PI/NUM_POINTS;
	if (alpharad < 0) {
		d_ang = - d_ang;
	} // end if

	for (float t=0; fabsf(t) < fabsf(anglim); t = t + d_ang) { 
		// mi fermo raggiunto alpharad; in un giro disegno NUM_POINTS punti.
		float x,y;
		x = xc -r*sinf(lonrad - t);
		y = yc + r*cosf(lonrad - t)*sinf(latrad);
		putpixel(bmp, x, y, color);
	} // end for

}
// circlerif_theta: disegna un arco di circonf in prospettiva per visualizzare theta
void circlerif_theta(BITMAP *bmp, int xc, int yc, int r, int l1, float alpharad, float thetarad,
		float lonrad, float latrad, int color) {
	// bmp, xc xcentro, yc ycentro, raggio cerchio, dimensione link1, alpharad, thetarad
	// lonrad angolo long vista asson, latrad " ", color colore
	float anglim = 0, d_ang; // angolo limite
	anglim = thetarad;
	d_ang = 2*M_PI/NUM_POINTS;
	if (thetarad < 0) {
		d_ang = - d_ang;
	} // end if

	for (float t=0; fabsf(t) < fabsf(anglim); t = t + d_ang) {
		// mi fermo raggiunto thetarad; in un giro disegno NUM_POINTS punti.
		float x,y;
		x = xc + cosf(lonrad)*(l1*sinf(alpharad) + r*cosf(alpharad)*sinf(t)) - sinf(lonrad)*(l1*cosf(alpharad) -
				r*sinf(alpharad)*sinf(t));
		y = yc + cosf(lonrad)*sinf(latrad)*(l1*cosf(alpharad) - r*sinf(alpharad)*sinf(t)) - r*cosf(latrad)*cosf(t) +
				sinf(latrad)*sinf(lonrad)*(l1*sinf(alpharad) + r*cosf(alpharad)*sinf(t));
		putpixel(bmp, x, y, color);
	} // end for
}
// circlerif_parup: disegna un cerchio parametrico che inizia dalla verticale
void circlerif_parup(BITMAP *bmp, int xc, int yc, int r, float ang, int color) {
	// bmp, xc xcentro, yc ycentro, raggio cerchio, ang angolo a cui fermarsi, color colores
	float anglim = 0, d_ang; // angolo limite
	anglim = ang;
	d_ang = 2*M_PI/NUM_POINTS;
	if (ang < 0) {
		d_ang = - d_ang;
	} // end if
	for (float t=0; fabsf(t) < fabsf(anglim); t = t + d_ang) {
		// mi fermo raggiunto ang, in un giro disegno NUM_POINTS punti
		float x,y;
		x = xc + r*sinf(t);
		y = yc - r*cosf(t);
		putpixel(bmp, x, y, color);
	} // end for

}
// proiez_asson proietto coordinate spaziali in coordinate di disegno secondo una proiezione assonometrica
Point proiez_asson(Vect P, AngleSinCos Lon, AngleSinCos Lat) {
	// P vettore x y z
	Point PAlleg;
	PAlleg.x = P.y*Lon.cos - P.x * Lon.sin;
	PAlleg.y = P.x*Lon.cos * Lat.sin - P.z* Lat.cos + P.y * Lat.sin*Lon.sin;
	return PAlleg;
}
// disegna griglia in assonometria
void grid(Vect P1, Vect P2, int q, int posx, int posy, AngleSinCos Lon, AngleSinCos Lat, int col) {
	int lx, ly;
	lx = abs(P1.x - P2.x);
	ly = abs(P1.y - P2.y);
	int dx, dy;
	dx = lx / q;
	dy = ly / q;

	Vect A, B;
	A = P1;
	B = P1; B.y += ly;
	Point a, b;

	//Parte X
	if (P1.x < P2.x) {
		for (int t=P1.x; t <= P2.x; t = t + dx) {
			A.x = t;
			B.x = t;
			a = proiez_asson(A, Lon, Lat); a.x += posx; a.y += posy;
			b = proiez_asson(B, Lon, Lat); b.x += posx; b.y += posy;
			line(scrbuf, a.x, a.y, b.x, b.y, col);
		} // end for
	}// end if
	if (P1.x > P2.x) {
		for (int t=P2.x; t <= P1.x; t = t + dx) {
			A.x = t;
			B.x = t;
			a = proiez_asson(A, Lon, Lat); a.x += posx; a.y += posy;
			b = proiez_asson(B, Lon, Lat); b.x += posx; b.y += posy;
			line(scrbuf, a.x, a.y, b.x, b.y, col);
		} // end for
	}// end if

	//Parte Y
	A = P1;
	B = P1; B.x += lx;
	if (P1.y < P2.y) {
		for (int t=P1.y; t <= P2.y; t = t + dy) {
			A.y = t;
			B.y = t;
			a = proiez_asson(A, Lon, Lat); a.x += posx; a.y += posy;
			b = proiez_asson(B, Lon, Lat); b.x += posx; b.y += posy;
			line(scrbuf, a.x, a.y, b.x, b.y, col);
		} // end for
	}// end if
	if (P1.y > P2.y) {
		for (int t=P2.y; t <= P1.y; t = t + dy) {
			A.y = t;
			B.y = t;
			a = proiez_asson(A, Lon, Lat); a.x += posx; a.y += posy;
			b = proiez_asson(B, Lon, Lat); b.x += posx; b.y += posy;
			line(scrbuf, a.x, a.y, b.x, b.y, col);
		} // end for
	}// end if

}
// disegna vista assonometrica
void vista_asson(AngleSinCos Alpha, AngleSinCos Theta, AngleSinCos Lon, AngleSinCos Lat, float alpharad, float thetarad,
		float lonrad, float latrad) {
	//--------------------
	// Vista Assonometrica
	rectfill(scrbuf, resetasson.x1, resetasson.y1, resetasson.x2, resetasson.y2, col.bck);	// reset
	int l1 = L1_ASSON, l2 = L2_ASSON;	//lunghezze aste

	Vect Arif, Prif;
	Arif.x = l1;
	Arif.y = 0;
	Arif.z = 0;
	Prif.x = l1*Alpha.cos;
	Prif.y = l1*Alpha.sin;
	Prif.z = l2;
	Vect A0, P0; // 0 indica il sistema di riferimento
	A0.x = l1*Alpha.cos;
	A0.y = l1*Alpha.sin;
	A0.z = 0;
	P0.x = l1*Alpha.cos - l2*Alpha.sin*Theta.sin;
	P0.y = l1*Alpha.sin + l2*Alpha.cos*Theta.sin;
	P0.z = l2*Theta.cos;

	TwoPoints riflink1asson, riflink2asson; //riferimenti link vista assonometrica
	riflink1asson.x1 = asson0.x;
	riflink1asson.y1 = asson0.y;
	riflink1asson.x1 = asson0.x;
	riflink1asson.y1 = asson0.y;
	riflink1asson.x2 = asson0.x + proiez_asson(Arif, Lon, Lat).x;
	riflink1asson.y2 = asson0.y + proiez_asson(Arif, Lon, Lat).y;
	riflink2asson.x1 = asson0.x + proiez_asson(A0, Lon, Lat).x;
	riflink2asson.y1 = asson0.y + proiez_asson(A0, Lon, Lat).y;
	riflink2asson.x2 = asson0.x + proiez_asson(Prif, Lon, Lat).x;
	riflink2asson.y2 = asson0.y + proiez_asson(Prif, Lon, Lat).y;

	TwoPoints link1asson, link2asson; //link vista assonometrica
	link1asson.x1 = asson0.x;
	link1asson.y1 = asson0.y;
	link1asson.x2 = asson0.x + proiez_asson(A0, Lon, Lat).x;
	link1asson.y2 = asson0.y + proiez_asson(A0, Lon, Lat).y;
	link2asson.x1 = asson0.x + proiez_asson(A0, Lon, Lat).x;
	link2asson.y1 = asson0.y + proiez_asson(A0, Lon, Lat).y;
	link2asson.x2 = asson0.x + proiez_asson(P0, Lon, Lat).x;
	link2asson.y2 = asson0.y + proiez_asson(P0, Lon, Lat).y;

	// Disegno riferimenti e oggeti

	//Griglia
	Vect P1, P2;
	P1.x = -LX_GRID/2; P1.y = -LY_GRID/2; P1.z = -l1;
	P2.x = +LX_GRID/2; P2.y = +LY_GRID/2; P2.z = -l1;
	grid(P1, P2, NUM_GRID, asson0.x, asson0.y, Lon, Lat, col.rif);
	//asse verticale
	thick_line(scrbuf, asson0.x, asson0.y + l1*Lat.cos, asson0.x, asson0.y, THICK+1, col.vert);
	line(scrbuf, riflink1asson.x1, riflink1asson.y1, riflink1asson.x2, riflink1asson.y2, col.rif); //rif link1
	line(scrbuf, riflink2asson.x1, riflink2asson.y1, riflink2asson.x2, riflink2asson.y2, col.rif); //rif link2
	circlerif_alpha(scrbuf, asson0.x, asson0.y, l1, alpharad, lonrad, latrad, col.rif); //rif alpha
	circlerif_theta(scrbuf, asson0.x, asson0.y, l2, l1, alpharad, thetarad, lonrad, latrad, col.rif); //rif theta

	// Disegno link
	thick_line(scrbuf, link1asson.x1, link1asson.y1, link1asson.x2, link1asson.y2, THICK, col.mdl); //link1
	thick_line(scrbuf, link2asson.x1, link2asson.y1, link2asson.x2, link2asson.y2, THICK, col.mdl2); //link2
}
// disegna vista lato
void vista_lato(AngleSinCos Theta, float thetarad) {
//--------------------
	// Vista lato
	rectfill(scrbuf, resetlato.x1, resetlato.y1, resetlato.x2, resetlato.y2, col.bck);	// reset
	int l2 = L2_LATO;
	TwoPoints link2lato;
	link2lato.x1 = lato0.x;
	link2lato.y1 = lato0.y;
	link2lato.x2 = lato0.x + l2 * Theta.sin;
	link2lato.y2 = lato0.y - l2 * Theta.cos;
	line(scrbuf, link2lato.x1, link2lato.y1, link2lato.x1, link2lato.y1 -l2, col.rif); // rif link lato
	circlerif_parup(scrbuf, lato0.x, lato0.y, l2, thetarad, col.rif); // rif angolo theta
	thick_line(scrbuf, link2lato.x1, link2lato.y1, link2lato.x2, link2lato.y2, THICK, col.mdl2); // link lato

}
// disegna vista alto
void vista_alto(AngleSinCos Alpha, float alpharad) {

	// Vista alto
	rectfill(scrbuf, resetalto.x1, resetalto.y1, resetalto.x2, resetalto.y2, col.bck); 	// reset
	int l1 = L1_ALTO;
	TwoPoints link1alto;
	link1alto.x1 = alto0.x;
	link1alto.y1 = alto0.y;
	link1alto.x2 = alto0.x - l1 * Alpha.sin;
	link1alto.y2 = alto0.y - l1 * Alpha.cos;
	line(scrbuf, link1alto.x1, link1alto.y1, link1alto.x1, link1alto.y1 - l1, col.rif); // rif link alto
	circlerif_parup(scrbuf, alto0.x, alto0.y, l1, -alpharad, col.rif); // rif angolo alpha
	thick_line(scrbuf, link1alto.x1, link1alto.y1, link1alto.x2, link1alto.y2, THICK, col.mdl); // link alto
}













