#include "gui.h"
#include <stdio.h>
#include <math.h>

//int dist;
static int colscr, colbck;
static int pos0xasso, pos0yasso, pos0xlato, pos0ylato, pos0xalto, pos0yalto;
static TwoPoints resetasso, resetlato, resetalto;
static int colmdl, colmdl2, colrif;

//Static GUI
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

	//----------------------------------
	// Calcoli per la grafica
	// posizione centrale rettangolo v.assonometrica
	pos0xasso = wrett1 + wrett2/2 + 2*dist;
	pos0yasso = hrett2/2 + dist; // posizione centrale rettangolo v.asson
	//pos0yasso += dist; // per fare spazio alla scritta
	// posizione centrale rettangolo v.lato
	pos0xlato = wrett1 + wrett3 + wrett4/2 + 2*dist;
	pos0ylato = hrett2 + hrett3/2 + dist;
	pos0ylato += dist;
	// posizione centrale rettangolo v.alto
	pos0xalto = wrett1 + wrett3/2 + 2*dist;
	pos0yalto = hrett2 + hrett3/2 + dist;
	pos0yalto += dist;
	// reset viste
	resetasso.x1 = wrett1 + 2*dist + 1;
	resetasso.y1 = dist + 1;
	resetasso.y1 += 2*dist;
	resetasso.x2 = wrett1 + wrett2 + 2*dist - 1;
	resetasso.y2 = hrett2 + dist - 1;
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
	// colori modello, rif
	colmdl = makecol(255, 0, 0);
	colmdl2 = makecol(255, 204, 0);
	colrif = makecol(128, 128, 128);

	return 0;
}

////////////
// GUI
void gui(Par par_old, Par par_new){
	// alpha angolo con il link orizzontale (gradi), theta angolo con il link verticale (gradi)
	// lon angolo vista asson longitudinale (gradi), lat angolo vista asson laterale (gradi)

	//--------------------
	char bustr[30], alphastr[30], thetastr[30];					// stringhe di comunicazione che vengono aggiornate

	//Angoli e grandezze fisiche
	float alpharad, thetarad, lonrad, latrad;					// porta gli angoli in rad

	// Potremmo fare delle flag per far calcolare i seni e i coseni solo nel caso cambiassero quegli angoli. Messo qui li calcola ogni volta anche se non cambia niente.
	// Al momento funziona cosi`:
	// Se non cambia niente calcolo una volta ma per niente
	// Se cambia una cosa sola calcolo una volta sola tutto
	// Se cambia tutto calcolo una volta sola tutto
	// ci penso se complicare il codice o meno
	alpharad = (float)par_new.alpha/180 *M_PI;
	thetarad = (float)par_new.theta /180 *M_PI;
	lonrad = (float)par_new.lon/180 * M_PI;
	latrad = (float)par_new.lat/180 * M_PI;

	AngleSinCos Alpha, Theta, Lon, Lat;
	Alpha.sin = sin(alpharad);	Alpha.cos = cos(alpharad);
	Theta.sin = sin(thetarad);	Theta.cos = cos(thetarad);
	Lat.sin = sin(latrad); Lat.cos = cos(latrad);
	Lon.sin = sin(lonrad); Lon.cos = cos(lonrad);

	//--------------------
	// SCRITTE
	if(par_new.alpha != par_old.alpha ||  par_new.theta != par_old.theta || par_new.lon != par_old.lon || par_new.lat != par_old.lat || par_new.bu != par_old.bu){
		// bu
		sprintf(bustr, "bu = %5.2f, a/z +-0.1  ", par_new.bu);
		textout_ex(screen, font, bustr, dist*2, dist*2, colscr, colbck);
		// alpha
		sprintf(alphastr, "alpha = %5.2f, k/l +-5  ", par_new.alpha);
		textout_ex(screen, font, alphastr, dist*2, dist*3, colscr, colbck);
		// theta
		sprintf(thetastr, "theta = %5.2f, i/o +-5  ", par_new.theta);
		textout_ex(screen, font, thetastr, dist*2, dist*4, colscr, colbck);
	}

	//--------------------
	// ANIMAZIONE
	if(par_new.alpha != par_old.alpha ||  par_new.theta != par_old.theta || par_new.lon != par_old.lon || par_new.lat != par_old.lat ){
		vista_assonometrica( Alpha,  Theta,  Lon,  Lat, alpharad,  thetarad, lonrad, latrad );
	}
	if( par_new.theta != par_old.theta){
		vista_lato(Theta, thetarad);
	}
	if(par_new.alpha != par_old.alpha ){
		vista_alto(Alpha, alpharad);
	}

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
void circlerif_alpha(BITMAP *bmp, int xc, int yc, int r, float alpharad, float lonrad, float latrad, int color){
	// bmp, xc xcentro, yc ycentro, raggio cerchio, alpharad, lonrad angolo long vista asson, latrad " ", color colore

	float anglim = 0, d_ang; // angolo limite
	anglim = alpharad;
	d_ang = 2*M_PI/NUM_POINTS;
	if(alpharad < 0){
		d_ang = - d_ang;
	} // end if

	for(float t=0; fabsf(t) < fabsf(anglim); t = t + d_ang){  // mi fermo raggiunto alpharad in un giro disegno NUM_POINTS punti.
		float x,y;
		x =  xc -r*sin(lonrad - t);
		y =  yc + r*cos(lonrad - t)*sin(latrad);
		putpixel(bmp, x, y, color);
	} // end for

}
// circlerif_theta: disegna un arco di circonf in prospettiva per visualizzare theta
void circlerif_theta(BITMAP *bmp, int xc, int yc, int r, int l1, float alpharad, float thetarad, float lonrad, float latrad, int color){
	// bmp, xc xcentro, yc ycentro, raggio cerchio, dimensione link1, alpharad, thetarad, lonrad angolo long vista asson, latrad " ", color colore
	float anglim = 0, d_ang; // angolo limite
	anglim = thetarad;
	d_ang = 2*M_PI/NUM_POINTS;
	if(thetarad < 0){
		d_ang = - d_ang;
	} // end if

	for(float t=0; fabsf(t) < fabsf(anglim); t = t + d_ang){  // mi fermo raggiunto thetarad; in un giro disegno NUM_POINTS punti.
		float x,y;
		x = xc + cos(lonrad)*(l1*sin(alpharad) + r*cos(alpharad)*sin(t)) - sin(lonrad)*(l1*cos(alpharad) - r*sin(alpharad)*sin(t));
		y = yc + cos(lonrad)*sin(latrad)*(l1*cos(alpharad) - r*sin(alpharad)*sin(t)) - r*cos(latrad)*cos(t) + sin(latrad)*sin(lonrad)*(l1*sin(alpharad) + r*cos(alpharad)*sin(t));
		putpixel(bmp, x, y, color);
	} // end for
}
// circlerif_parup: disegna un cerchio parametrico che inizia dalla verticale
void circlerif_parup(BITMAP *bmp, int xc, int yc, int r, float ang, int color){
	// bmp, xc xcentro, yc ycentro, raggio cerchio, ang angolo a cui fermarsi, color colores
	float anglim = 0, d_ang; // angolo limite
	anglim = ang;
	d_ang = 2*M_PI/NUM_POINTS;
	if(ang < 0){
		d_ang = - d_ang;
	} // end if
	for(float t=0; fabsf(t) < fabsf(anglim); t = t + d_ang){  // mi fermo raggiunto ang, in un giro disegno NUM_POINTS punti
		float x,y;
		x = xc + r*sin(t);
		y = yc - r*cos(t);
		putpixel(bmp, x, y, color);
	} // end for

}
/*/// circlerif_pardown: disegna un cerchio parametrico che inizia dalla verticale
void circlerif_pardown(BITMAP *bmp, int xc, int yc, int r, float *ang, int color){
	// bmp, xc xcentro, yc ycentro, raggio cerchio, ang angolo a cui fermarsi, color colores
	float anglim = 0, d_ang; // angolo limite
	anglim = *ang;
	d_ang = 2*M_PI/NUM_POINTS;
	if(*ang < 0){
		d_ang = - d_ang;
	} // end if
	for(float t=0; fabsf(t) < fabsf(anglim); t = t + d_ang){  // mi fermo raggiunto ang, in un giro disegno NUM_POINTS punti
		float x,y;
		x = xc + r*sin(t);
		y = yc + r*cos(t);
		putpixel(bmp, x, y, color);
	} // end for
}*/

// proiez_ass proietto coordinate spaziali in coordinate di disegno secondo una proiezione assonometrica
Point proiez_ass(Vect P, AngleSinCos Lon, AngleSinCos Lat){
	// P vettore x y z
	Point PAlleg;
	PAlleg.x = P.y*Lon.cos - P.x * Lon.sin;
	PAlleg.y = P.x*Lon.cos * Lat.sin - P.z* Lat.cos + P.y * Lat.sin*Lon.sin;
	return PAlleg;
}

// disegna griglia in assonometria
void grid(Vect P1, Vect P2, int q, int posx, int posy, AngleSinCos Lon, AngleSinCos Lat, int col){
	int lx, ly;
	lx = fabsf( P1.x - P2.x );
	ly = fabsf( P1.y - P2.y );
	int dx, dy;
	dx = lx / q;
	dy = ly / q;

	Vect A, B;
	A = P1;
	B = P1; B.y += ly;
	Point a, b;

	//Parte X
	if(P1.x < P2.x){
		for(int t=P1.x; t <=  P2.x; t = t + dx ){
			A.x = t;
			B.x = t;
			a = proiez_ass(A, Lon, Lat); a.x += posx; a.y += posy;
			b = proiez_ass(B, Lon, Lat); b.x += posx; b.y += posy;
			line(screen, a.x, a.y, b.x, b.y, col);
		} // end for
	}// end if
	if(P1.x > P2.x){
		for(int t=P2.x; t <=  P1.x; t = t + dx ){
			A.x = t;
			B.x = t;
			a = proiez_ass(A, Lon, Lat); a.x += posx; a.y += posy;
			b = proiez_ass(B, Lon, Lat); b.x += posx; b.y += posy;
			line(screen, a.x, a.y, b.x, b.y, col);
		} // end for
	}// end if

	//Parte Y
	A = P1;
	B = P1; B.x += lx;
	if(P1.y < P2.y){
		for(int t=P1.y; t <=  P2.y; t = t + dy ){
			A.y = t;
			B.y = t;
			a = proiez_ass(A, Lon, Lat); a.x += posx; a.y += posy;
			b = proiez_ass(B, Lon, Lat); b.x += posx; b.y += posy;
			line(screen, a.x, a.y, b.x, b.y, col);
		} // end for
	}// end if
	if(P1.y > P2.y){
		for(int t=P2.y; t <=  P1.y; t = t + dy ){
			A.y = t;
			B.y = t;
			a = proiez_ass(A, Lon, Lat); a.x += posx; a.y += posy;
			b = proiez_ass(B, Lon, Lat); b.x += posx; b.y += posy;
			line(screen, a.x, a.y, b.x, b.y, col);
		} // end for
	}// end if

}


void vista_assonometrica(AngleSinCos Alpha, AngleSinCos Theta, AngleSinCos Lon,  AngleSinCos Lat, float alpharad, float thetarad, float lonrad, float latrad ){
//--------------------
	// Vista Assonometrica
	rectfill(screen, resetasso.x1, resetasso.y1, resetasso.x2, resetasso.y2, colbck);	// reset
	int l1 = L1_ASSO, l2 = L2_ASSO;	//lunghezze aste

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

	TwoPoints riflink1ass, riflink2ass; //riferimenti link vista assonometrica
	riflink1ass.x1 = pos0xasso;
	riflink1ass.y1 = pos0yasso;
	riflink1ass.x1 = pos0xasso;
	riflink1ass.y1 = pos0yasso;
	riflink1ass.x2 = pos0xasso + proiez_ass(Arif, Lon, Lat).x;
	riflink1ass.y2 = pos0yasso + proiez_ass(Arif, Lon, Lat).y;
	riflink2ass.x1 = pos0xasso + proiez_ass(A0, Lon, Lat).x;
	riflink2ass.y1 = pos0yasso + proiez_ass(A0, Lon, Lat).y;
	riflink2ass.x2 = pos0xasso + proiez_ass(Prif, Lon, Lat).x;
	riflink2ass.y2 = pos0yasso + proiez_ass(Prif, Lon, Lat).y;

	TwoPoints link1ass, link2ass; //link vista assonometrica
	link1ass.x1 = pos0xasso;
	link1ass.y1 = pos0yasso;
	link1ass.x2 = pos0xasso + proiez_ass(A0, Lon, Lat).x;
	link1ass.y2 = pos0yasso + proiez_ass(A0, Lon, Lat).y;
	link2ass.x1 = pos0xasso + proiez_ass(A0, Lon, Lat).x;
	link2ass.y1 = pos0yasso + proiez_ass(A0, Lon, Lat).y;
	link2ass.x2 = pos0xasso + proiez_ass(P0, Lon, Lat).x;
	link2ass.y2 = pos0yasso + proiez_ass(P0, Lon, Lat).y;

	// Disegno riferimenti e oggeti

	//Griglia
	Vect P1, P2;
	P1.x = -LX_GRID/2; P1.y = -LY_GRID/2; P1.z = -l1;
	P2.x = +LX_GRID/2; P2.y = +LY_GRID/2; P2.z = -l1;
	grid(P1, P2, NUM_GRID, pos0xasso, pos0yasso, Lon, Lat, colrif);
	//asse verticale
	thick_line(screen, pos0xasso, pos0yasso + l1*Lat.cos, pos0xasso, pos0yasso, THICK+1, makecol(0,0,0));
	line(screen, riflink1ass.x1, riflink1ass.y1, riflink1ass.x2, riflink1ass.y2, colrif); //rif link1
	line(screen, riflink2ass.x1, riflink2ass.y1, riflink2ass.x2, riflink2ass.y2, colrif); //rif link2
	circlerif_alpha(screen, pos0xasso, pos0yasso, l1, alpharad, lonrad, latrad, colrif); //rif alpha
	circlerif_theta(screen, pos0xasso, pos0yasso, l2, l1, alpharad, thetarad, lonrad, latrad, colrif); //rif theta

	// Disegno link
	thick_line(screen, link1ass.x1, link1ass.y1, link1ass.x2, link1ass.y2, THICK, colmdl); //link1
	thick_line(screen, link2ass.x1, link2ass.y1, link2ass.x2, link2ass.y2, THICK, colmdl2); //link2
}


void vista_lato(AngleSinCos Theta, float thetarad){
//--------------------
	// Vista lato
	rectfill(screen, resetlato.x1, resetlato.y1, resetlato.x2, resetlato.y2, colbck);	// reset
	int l2 = L2_LATO;
	TwoPoints link2lato;
	link2lato.x1 = pos0xlato;
	link2lato.y1 = pos0ylato;
	link2lato.x2 = pos0xlato + l2 * Theta.sin;
	link2lato.y2 = pos0ylato - l2 * Theta.cos;
	line(screen, link2lato.x1, link2lato.y1, link2lato.x1, link2lato.y1 -l2, colrif); // rif link lato
	circlerif_parup(screen, pos0xlato, pos0ylato, l2, thetarad, colrif); // rif angolo theta
	thick_line(screen, link2lato.x1, link2lato.y1, link2lato.x2, link2lato.y2, THICK, colmdl2); // link lato

}

void vista_alto(AngleSinCos Alpha, float alpharad){

	// Vista alto
	rectfill(screen, resetalto.x1, resetalto.y1, resetalto.x2, resetalto.y2, colbck); 	// reset
	int l1 = L1_ALTO;
	TwoPoints link1alto;
	link1alto.x1 = pos0xalto;
	link1alto.y1 = pos0yalto;
	link1alto.x2 = pos0xalto + l1 * Alpha.sin;
	link1alto.y2 = pos0yalto - l1 * Alpha.cos;
	line(screen, link1alto.x1, link1alto.y1, link1alto.x1, link1alto.y1 - l1, colrif); // rif link alto
	circlerif_parup(screen, pos0xalto, pos0yalto, l1, alpharad, colrif); // rif angolo alpha
	thick_line(screen, link1alto.x1, link1alto.y1, link1alto.x2, link1alto.y2, THICK, colmdl); // link alto
}













