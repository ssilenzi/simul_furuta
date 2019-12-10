#include "gui.h"


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
	int y[(int)(HSCREEN/DIST - 2)];
} scritte; // array per scrivere "parametricamente" le scritte

//----------- init gui
int gui_init(){
	// Init allegro
	if (allegro_init() != 0)
		return 1;
	set_color_depth(COLOR_DEPTH); 	// RGB mode (32 bits)
	install_keyboard();		//posso usare la tastiera

	// dimensioni dei rettangoli
	int hrett1 = HSCREEN - 2 * DIST; // altezza rettangolo 1
	int wrett5 = WSCREEN - 3 * DIST - WRETT1;
	int hrett3 = wrett5 / 2;
	int wrett3 = wrett5 / 2;
	int hrett4 = hrett3;
	int wrett4 = wrett3;
	int hrett2 = HSCREEN - 2 * DIST - hrett3;
	int wrett2 = wrett5;

	int qdistvert = HSCREEN/ DIST - 2; // quante DIST entrano dentro il mio schermo, dimensione dell'array scritte
	scritte.x = 2*DIST;
	for (int i = 0; i < qdistvert; i++) {
		scritte.y[i] = DIST * (i+1);
	} //popolo l'array scritte con le posizioni xy delle scritte

	if (set_gfx_mode(GRAFICA, WSCREEN, HSCREEN, 0, 0) != 0) {
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
		return 1;
	}

	scrbuf = create_bitmap(SCREEN_W, SCREEN_H);
	if (!scrbuf) {
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Unable to initialize page flipping\n");
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

	// Disegno rettangoli e elementi statici
	//rett1 - parametri, sinistra
	rect(scrbuf, DIST, DIST, DIST + WRETT1, DIST + hrett1, col.rett);
	char exit[50], reset1[50], reset2[50], reset3[50], reset4[50], state_pause[50],control_pause[50];
	sprintf(exit, "Premere Esc per uscire");
	textout_ex(scrbuf, font, exit, scritte.x, scritte.y[qdistvert-1], col.scr, col.bck);

	sprintf(reset1, "R per resettare stato e riferimento");
	textout_ex(scrbuf, font, reset1, scritte.x, scritte.y[qdistvert-2], col.scr, col.bck);

	sprintf(reset2, "Up, down, left right per modificare la vista");
	textout_ex(scrbuf, font, reset2, scritte.x, scritte.y[qdistvert-3], col.scr, col.bck);

	sprintf(reset3, "T per resettare la vista");
	textout_ex(scrbuf, font, reset3, scritte.x, scritte.y[qdistvert-4], col.scr, col.bck);

    sprintf(state_pause, "A pause/unpause la simulazione");
	textout_ex(scrbuf, font, state_pause, scritte.x, scritte.y[qdistvert-5], col.scr, col.bck);
	
    sprintf(control_pause, "S pause/unpause il controllo");
	textout_ex(scrbuf, font, control_pause, scritte.x, scritte.y[qdistvert-6], col.scr, col.bck);
	
	sprintf(reset4, "E per resettare i parametri del controllore");
	textout_ex(scrbuf, font, reset4, scritte.x, scritte.y[qdistvert-7], col.scr, col.bck);
	
	
	
	TwoPoints rett_asso, rett_alto, rett_lato;
	Point titolo_asso, titolo_alto, titolo_lato;
	char assonstr[50], altostr[50], latostr[50];
	//rett2 - Vista assonometrica
	rett_asso.x1 = DIST + WRETT1 + DIST;
	rett_asso.y1 = DIST;
	rett_asso.x2 = DIST + WRETT1 + DIST + wrett2;
	rett_asso.y2 = DIST + hrett2;
	rect(scrbuf, rett_asso.x1, rett_asso.y1, rett_asso.x2, rett_asso.y2, col.rett);
	sprintf(assonstr, "Vista Assonometrica");
	titolo_asso.x = DIST + WRETT1 + DIST + wrett2 /2 - 3.5*DIST;
	titolo_asso.y = 2*DIST;
	textout_ex(scrbuf, font, assonstr, titolo_asso.x, titolo_asso.y, col.scr, col.bck);
	//rett3 - vista alto
	rett_alto.x1 = DIST + WRETT1 + DIST;
	rett_alto.y1 = DIST + hrett2;
	rett_alto.x2 = DIST + WRETT1 + DIST + wrett3;
	rett_alto.y2 = DIST + hrett2 + hrett3;
	rect(scrbuf, rett_alto.x1, rett_alto.y1, rett_alto.x2, rett_alto.y2, col.rett);
	sprintf(altostr, "Vista Alto");
	titolo_alto.x = DIST + WRETT1 + DIST + wrett3 /2 - 2.1*DIST;
	titolo_alto.y = DIST + hrett2 + DIST;
	textout_ex(scrbuf, font, altostr, titolo_alto.x, titolo_alto.y,	col.scr, col.bck);
	//rett4 - vista Lato
	rett_lato.x1 = DIST + WRETT1 + DIST + wrett3;
	rett_lato.y1 = DIST + hrett2;
	rett_lato.x2 = DIST + WRETT1 + DIST + wrett3 + wrett4;
	rett_lato.y2 = DIST + hrett2 + hrett4;
	rect(scrbuf, rett_lato.x1, rett_lato.y1, rett_lato.x2, rett_lato.y2, col.rett);
	sprintf(latostr, "Vista Lato");
	titolo_lato.x = DIST + WRETT1 + DIST + wrett3 + wrett4/2 - 2.1*DIST;
	titolo_lato.y = DIST + hrett2 + DIST;
	textout_ex(scrbuf, font, latostr, titolo_lato.x, titolo_lato.y, col.scr, col.bck);

	//----------------------------------
	// Calcoli per la grafica
	// posizione centrale rettangolo v.assonometrica
	asson0.x = WRETT1 + wrett2/2 + 2*DIST;
	asson0.y = hrett2/2 + DIST; // posizione centrale rettangolo v.asson
	// posizione centrale rettangolo v.lato
	lato0.x = WRETT1 + wrett3 + wrett4/2 + 2*DIST;
	lato0.y = hrett2 + hrett3/2 + DIST;
	lato0.y += DIST;
	// posizione centrale rettangolo v.alto
	alto0.x = WRETT1 + wrett3/2 + 2*DIST;
	alto0.y = hrett2 + hrett3/2 + DIST;
	alto0.y += DIST;
	// reset viste
	resetasson.x1 = WRETT1 + 2*DIST + 1;
	resetasson.y1 = DIST + 1;
	resetasson.y1 += 2*DIST;
	resetasson.x2 = WRETT1 + wrett2 + 2*DIST - 1;
	resetasson.y2 = hrett2 + DIST - 1;
	resetalto.x1 = WRETT1 + 2*DIST + 1;
	resetalto.y1 = hrett2 + DIST + 1;
	resetalto.y1 += 2*DIST;
	resetalto.x2 = WRETT1 + wrett3 + 2*DIST - 1;
	resetalto.y2 = hrett2 + hrett3 + DIST - 1;
	resetlato.x1 = WRETT1 + wrett3 + 2*DIST + 1;
	resetlato.y1 = hrett2 + DIST + 1;
	resetlato.y1 += 2*DIST;
	resetlato.x2 = WRETT1 + wrett3 + wrett4 + 2*DIST - 1;
	resetlato.y2 = hrett2 + hrett4 + DIST - 1;

	return 0;
}

//----------- gui
void* gui(void* arg){
	int id;							// task index
	id = get_task_index(arg);		// retrieve the task index
	set_activation(id);
	
	static State state_old = 
		{ALPHA_0+1, 
		ALPHADOT_0+1,
		THETA_0+1,
		THETADOT_0+1,
		CURRENT_0+1,
		VOLTAGE_0+1,
		CCR_0+1,
		ENC_ALPHA_0+1,
		ENC_THETA_0+1
		};
	static State state_new;
    static Ref ref_old = {1, 1};
	static Ref ref_new = {1, 1};
	static View view_old = {1, 1};
	static View view_new = {1, 1};

	static Par_control par_control_old = {KP_ALPHA_DEF+1, KD_ALPHA_DEF+1, KP_THETA_DEF+1, KD_THETA_DEF+1, KSU_DEF +1};
	static Par_control par_control_new = {KP_ALPHA_DEF+1, KD_ALPHA_DEF+1, KP_THETA_DEF+1, KD_THETA_DEF+1, KSU_DEF +1};

	char refalphastr[30], alphastr[30], thetastr[30],voltagestr[14]; // stringhe di comunicazione che vengono aggiornate
	char parcontrstralpha[30], parcontrstrtheta[30],parcontrstrsu[22];	
	int draw = 0;		// flag per ridisegnare o meno l'interfaccia
	
	while(!end){
		// rendo locali le variabili, cosi` da usare un solo semaforo
		pthread_mutex_lock(&mux_state);
			state_new = state;
		pthread_mutex_unlock(&mux_state);
		pthread_mutex_lock(&mux_ref);
			ref_new = ref;
		pthread_mutex_unlock(&mux_ref);
		pthread_mutex_lock(&mux_state);
			view_new = view;
		pthread_mutex_unlock(&mux_state);
		pthread_mutex_lock(&mux_parcontr);
			par_control_new = par_control;
		pthread_mutex_unlock(&mux_parcontr);
	
		
		// ANIMAZIONE
		if (state_new.alpha != state_old.alpha || ref_new.alpha != ref_old.alpha) {
			vista_alto(state_new.alpha, ref_new.alpha);
			draw = 1;
		}

		if (state_new.theta != state_old.theta || ref_new.theta != ref_old.theta) {
			vista_lato(state_new.theta, ref_new.theta);
			draw = 1;
		}

		if (state_new.alpha != state_old.alpha || ref_new.alpha != ref_old.alpha || state_new.theta != state_old.theta ||
			ref_new.theta != ref_old.theta || view_new.lon != view_old.lon || view_new.lat != view_old.lat) {
			vista_asson(state_new.alpha, ref_new.alpha, state_new.theta, ref_new.theta, view_new.lon, view_new.lat);
			draw = 1;
		}

		// SCRITTE
		if (state_new.alpha != state_old.alpha || state_new.theta != state_old.theta || ref_new.alpha != ref_old.alpha || par_control_new.ksu != par_control_old.ksu ||par_control_new.alpha_kd != par_control_old.alpha_kd ||par_control_new.alpha_kp != par_control_old.alpha_kp ||par_control_new.theta_kd != par_control_old.alpha_kd|| par_control_new.theta_kp != par_control_old.theta_kp) 
		{

			// Riferimento
			textout_ex(scrbuf, font, "Riferimento:", scritte.x, scritte.y[1], col.scr, col.bck);
			sprintf(refalphastr, "alpha = %5.2f, i/o -+%d  ", ref_new.alpha, INCR_ANG);
			textout_ex(scrbuf, font, refalphastr, scritte.x, scritte.y[2], col.scr, col.bck);
			// Stato
			textout_ex(scrbuf, font, "Stato:", scritte.x, scritte.y[4], col.scr, col.bck);
			sprintf(alphastr, "alpha = %5.2f, k/l -+%d     ", state_new.alpha, INCR_ANG);
			textout_ex(scrbuf, font, alphastr, scritte.x, scritte.y[5], col.scr, col.bck);
			sprintf(thetastr, "theta = %5.2f, n/m -+%d     ", state_new.theta, INCR_ANG);
			textout_ex(scrbuf, font, thetastr,scritte.x, scritte.y[6], col.scr, col.bck);
			sprintf(voltagestr, "Volt = %5.2fV", state_new.voltage);
			textout_ex(scrbuf, font, voltagestr,scritte.x, scritte.y[7], col.scr, col.bck);
			// Par control
			textout_ex(scrbuf, font, "Parametri dei controllori:", scritte.x, scritte.y[9], col.scr, col.bck);
			sprintf(parcontrstralpha, "Alpha: Kp = %5.2f, Kd = %5.2f", par_control_new.alpha_kp, par_control_new.alpha_kd);
			textout_ex(scrbuf, font, parcontrstralpha,scritte.x, scritte.y[10], col.scr, col.bck);
			sprintf(parcontrstrtheta, "Theta: Kp = %5.2f, Kd = %5.2f", par_control_new.theta_kp, par_control_new.theta_kd);
			textout_ex(scrbuf, font, parcontrstrtheta,scritte.x, scritte.y[11], col.scr, col.bck);
			sprintf(parcontrstrsu, "Swing Up: Ksu = %5.2f", par_control_new.ksu);
			textout_ex(scrbuf, font, parcontrstrsu,scritte.x, scritte.y[12], col.scr, col.bck);
			
			draw = 1;
		}

		if (draw) blit(scrbuf, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		state_old = state_new; ref_old = ref_new; view_old = view_new; par_control_old=par_control_new;
		
		wait_for_period(id);		// wait to next period
	}
	return 0;
}

//----------- rad
float rad(float ang) {
    return ang / 180 * M_PI;
}

//----------- thick_line
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

//----------- Circle_rifalpha: disegno un arco di circonf in prospettiva per visualizzare alpha
void circlerif_alpha(BITMAP *bmp, Point C, int r, AngleSinCos Lon, AngleSinCos Lat, float alpha, float refalpha,
					 int color) {
	float initial, final, step;
	Vect P; Point PAlleg;

	step = 2*M_PI/NUM_POINTS;

	if (alpha < refalpha) {
		initial = rad(alpha);
		final = rad(refalpha);
	} else {
		initial = rad(refalpha);
		final = rad(alpha);
	}// end if

	for (float t = initial; t < final; t = t + step) {
		// mi fermo raggiunto alpharad; in un giro disegno NUM_POINTS punti.
		P.x = r*cosf(t);
		P.y = r*sinf(t);
		P.z = 0;
		PAlleg = proiez_asson(P, Lon, Lat);
		putpixel(bmp, C.x + PAlleg.x, C.y + PAlleg.y, color);
	} // end for
}
//----------- circlerif_theta: disegna un arco di circonf in prospettiva per visualizzare theta
void circlerif_theta(BITMAP *bmp, Point C, int r, int l1, AngleSinCos Alpha, AngleSinCos Lon, AngleSinCos Lat,
					 float theta, float reftheta, int color) {
	float initial, final, step;
	Vect P; Point PAlleg;

	step = 2*M_PI/NUM_POINTS;

	if (theta < reftheta) {
		initial = rad(theta);
		final = rad(reftheta);
	} else {
		initial = rad(reftheta);
		final = rad(theta);
	}// end if

	for (float t = initial; t < final; t = t + step) {
		// mi fermo raggiunto thetarad; in un giro disegno NUM_POINTS punti.
		P.x = l1*Alpha.cos - r*Alpha.sin*sinf(t);
		P.y = l1*Alpha.sin + r*Alpha.cos*sinf(t);
		P.z = r*cosf(t);
		PAlleg = proiez_asson(P, Lon, Lat);
		putpixel(bmp, C.x + PAlleg.x, C.y + PAlleg.y, color);
	} // end for
}
//----------- circlerif_parup: disegna un cerchio parametrico che inizia dalla verticale
void circlerif_parup(BITMAP *bmp, Point C, int r, float ang, float refang, int color) {
	float initial, final, step;
	Point PAlleg;

	step = 2*M_PI/NUM_POINTS;

	if (ang < refang) {
		initial = rad(ang);
		final = rad(refang);
	} else {
		initial = rad(refang);
		final = rad(ang);
	}// end if

	for (float t = initial; t < final; t = t + step) {
		// mi fermo raggiunto ang, in un giro disegno NUM_POINTS punti
		PAlleg.x = r*sinf(t);
		PAlleg.y = - r*cosf(t);
		putpixel(bmp, C.x + PAlleg.x, C.y + PAlleg.y, color);
	} // end for

}
//-----------  proiez_asson proietto coordinate spaziali in coordinate di disegno secondo una proiezione assonometrica
Point proiez_asson(Vect P, AngleSinCos Lon, AngleSinCos Lat) {
	Point PAlleg;
	PAlleg.x = P.y*Lon.cos - P.x * Lon.sin;
	PAlleg.y = P.x*Lon.cos * Lat.sin - P.z* Lat.cos + P.y * Lat.sin*Lon.sin;
	return PAlleg;
}
//----------- grid, disegna griglia in assonometria
void grid(Vect P1, Vect P2, int q, int posx, int posy, AngleSinCos Lon, AngleSinCos Lat, int col) {
	int lx, ly;
	int dx, dy;
	Vect A, B;
	Point a, b;

	lx = fabsf(P1.x - P2.x);
	ly = fabsf(P1.y - P2.y);
	dx = lx / q;
	dy = ly / q;
	A = P1;
	B = P1; B.y += ly;

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
//----------- vista_asson, disegna vista assonometrica
void vista_asson(float alpha, float refalpha, float theta, float reftheta, float lon, float lat) {
	int l1 = L1_ASSON, l2 = L2_ASSON;	//lunghezze aste
	AngleSinCos Alpha, RefAlpha, Theta, RefTheta, Lon, Lat;
	Vect Arif, Prif;
	Vect A0, P0; // rif, 0 indicano il sistema di riferimento
	TwoPoints riflink1asson, riflink2asson; // riferimenti link vista assonometrica
	TwoPoints link1asson, link2asson; // link vista assonometrica
	Vect P1, P2; // griglia

	Alpha.sin = sinf(rad(alpha));	Alpha.cos = cosf(rad(alpha));
	RefAlpha.sin = sinf(rad(refalpha)); RefAlpha.cos = cosf(rad(refalpha));
	Theta.sin = sinf(rad(theta));	Theta.cos = cosf(rad(theta));
	RefTheta.sin = sinf(rad(reftheta)); RefTheta.cos = cosf(rad(reftheta));
	Lat.sin = sinf(rad(lat)); Lat.cos = cosf(rad(lat));
	Lon.sin = sinf(rad(lon)); Lon.cos = cosf(rad(lon));

	// Reset della vista
	rectfill(scrbuf, resetasson.x1, resetasson.y1, resetasson.x2, resetasson.y2, col.bck);

	Arif.x = l1*RefAlpha.cos;
	Arif.y = l1*RefAlpha.sin;
	Arif.z = 0;
	Prif.x = l1*Alpha.cos - l2*Alpha.sin*RefTheta.sin;
	Prif.y = l1*Alpha.sin + l2*Alpha.cos*RefTheta.sin;
	Prif.z = l2*RefTheta.cos;

	A0.x = l1*Alpha.cos;
	A0.y = l1*Alpha.sin;
	A0.z = 0;
	P0.x = l1*Alpha.cos - l2*Alpha.sin*Theta.sin;
	P0.y = l1*Alpha.sin + l2*Alpha.cos*Theta.sin;
	P0.z = l2*Theta.cos;

	riflink1asson.x1 = asson0.x;
	riflink1asson.y1 = asson0.y;
	riflink1asson.x2 = asson0.x + proiez_asson(Arif, Lon, Lat).x;
	riflink1asson.y2 = asson0.y + proiez_asson(Arif, Lon, Lat).y;
	riflink2asson.x1 = asson0.x + proiez_asson(A0, Lon, Lat).x;
	riflink2asson.y1 = asson0.y + proiez_asson(A0, Lon, Lat).y;
	riflink2asson.x2 = asson0.x + proiez_asson(Prif, Lon, Lat).x;
	riflink2asson.y2 = asson0.y + proiez_asson(Prif, Lon, Lat).y;

	link1asson.x1 = asson0.x;
	link1asson.y1 = asson0.y;
	link1asson.x2 = asson0.x + proiez_asson(A0, Lon, Lat).x;
	link1asson.y2 = asson0.y + proiez_asson(A0, Lon, Lat).y;
	link2asson.x1 = asson0.x + proiez_asson(A0, Lon, Lat).x;
	link2asson.y1 = asson0.y + proiez_asson(A0, Lon, Lat).y;
	link2asson.x2 = asson0.x + proiez_asson(P0, Lon, Lat).x;
	link2asson.y2 = asson0.y + proiez_asson(P0, Lon, Lat).y;

	// Disegno riferimenti e oggeti

	// Griglia
	P1.x = -LX_GRID/2; P1.y = -LY_GRID/2; P1.z = -l1;
	P2.x = +LX_GRID/2; P2.y = +LY_GRID/2; P2.z = -l1;
	grid(P1, P2, NUM_GRID, asson0.x, asson0.y, Lon, Lat, col.rif);
	// asse verticale
	thick_line(scrbuf, asson0.x, asson0.y + l1*Lat.cos, asson0.x, asson0.y, THICK+1, col.vert);
	line(scrbuf, riflink1asson.x1, riflink1asson.y1, riflink1asson.x2, riflink1asson.y2, col.rif); //rif link1
	line(scrbuf, riflink2asson.x1, riflink2asson.y1, riflink2asson.x2, riflink2asson.y2, col.rif); //rif link2
	circlerif_alpha(scrbuf, asson0, l1, Lon, Lat, alpha, refalpha, col.rif); //rif alpha
	circlerif_theta(scrbuf, asson0, l2, l1, Alpha, Lon, Lat, theta, reftheta, col.rif); //rif theta

	// Disegno link
	thick_line(scrbuf, link1asson.x1, link1asson.y1, link1asson.x2, link1asson.y2, THICK, col.mdl); //link1
	thick_line(scrbuf, link2asson.x1, link2asson.y1, link2asson.x2, link2asson.y2, THICK, col.mdl2); //link2
}
//----------- vista_lato, disegna vista lato
void vista_lato(float theta, float reftheta) {
	int l2 = L2_LATO;
	AngleSinCos Theta, RefTheta;
	TwoPoints riflink2lato, link2lato;

	Theta.sin = sinf(rad(theta));	Theta.cos = cosf(rad(theta));
	RefTheta.sin = sinf(rad(reftheta)); RefTheta.cos = cosf(rad(reftheta));

	// Reset della vista
	rectfill(scrbuf, resetlato.x1, resetlato.y1, resetlato.x2, resetlato.y2, col.bck);

	riflink2lato.x1 = lato0.x;
	riflink2lato.y1 = lato0.y;
	riflink2lato.x2 = lato0.x + l2 * RefTheta.sin;
	riflink2lato.y2 = lato0.y - l2 * RefTheta.cos;
	link2lato.x1 = lato0.x;
	link2lato.y1 = lato0.y;
	link2lato.x2 = lato0.x + l2 * Theta.sin;
	link2lato.y2 = lato0.y - l2 * Theta.cos;
	line(scrbuf, riflink2lato.x1, riflink2lato.y1, riflink2lato.x2, riflink2lato.y2, col.rif); // rif link lato
	circlerif_parup(scrbuf, lato0, l2, theta, reftheta, col.rif); // rif angolo theta
	thick_line(scrbuf, link2lato.x1, link2lato.y1, link2lato.x2, link2lato.y2, THICK, col.mdl2); // link lato
}
// vista_alto, disegna vista alto
void vista_alto(float alpha, float refalpha) {
	int l1 = L1_ALTO;
	AngleSinCos Alpha, RefAlpha;
	TwoPoints riflink1alto, link1alto;

	Alpha.sin = sinf(rad(alpha));	Alpha.cos = cosf(rad(alpha));
	RefAlpha.sin = sinf(rad(refalpha)); RefAlpha.cos = cosf(rad(refalpha));

	// Reset della vista
	rectfill(scrbuf, resetalto.x1, resetalto.y1, resetalto.x2, resetalto.y2, col.bck);

	riflink1alto.x1 = alto0.x;
	riflink1alto.y1 = alto0.y;
	riflink1alto.x2 = alto0.x - l1 * RefAlpha.sin;
	riflink1alto.y2 = alto0.y - l1 * RefAlpha.cos;
	link1alto.x1 = alto0.x;
	link1alto.y1 = alto0.y;
	link1alto.x2 = alto0.x - l1 * Alpha.sin;
	link1alto.y2 = alto0.y - l1 * Alpha.cos;
	line(scrbuf, riflink1alto.x1, riflink1alto.y1, riflink1alto.x2, riflink1alto.y2, col.rif); // rif link alto
	circlerif_parup(scrbuf, alto0, l1, -alpha, -refalpha, col.rif); // rif angolo alpha
	thick_line(scrbuf, link1alto.x1, link1alto.y1, link1alto.x2, link1alto.y2, THICK, col.mdl); // link alto
}













