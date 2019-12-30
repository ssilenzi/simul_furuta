#ifndef CONDIVISO_H
	#define CONDIVISO_H

#include <stdbool.h>
#include <pthread.h>

//----------- costanti, definizioni
// stato, _0 iniziale 
#define ALPHA_0				0
#define ALPHADOT_0			0
#define THETA_0				0
#define THETADOT_0			0
#define CURRENT_0			0
#define VOLTAGE_0			0
#define CCR_0				2625 // meta` del range 0-5250
#define ENC_ALPHA_0			0
#define ENC_THETA_0			0

// view
#define LON_0				45		// longitudine iniziale
#define LAT_0				35		// latitudine iniziale
#define LAT_MAX				90
#define INCR_ANG			5

// gui
#define GRAFICA_LINUX		GFX_AUTODETECT_WINDOWED
#define GRAFICA_WIN32		GFX_GDI
#define WSCREEN				1024	// larghezza finestra
#define HSCREEN				768		// altezza finestra
#define COLOR_DEPTH			32		// numero colori
#define DIST				20		// unita` di misura per distanziare oggetti all'interno della finestra
#define WRETT1				400		//
#define L1_ASSON			133		// lunghezza link 1 vista assonometrica
#define L2_ASSON			100		// lunghezza link 2 vista assonometrica
#define L1_ALTO				 100		// lunghezza link 1 vista dall'alto
#define L2_LATO				100		// lunghezza link 2 vista di lato
#define LX_GRID				180		// lunghezza lungo x griglia nella vista assonometrica
#define LY_GRID				200		// lunghezza lungo y griglia nella vista assonometrica
#define NUM_GRID			5		// numero di linee da disegnare nella griglia
#define NUM_POINTS			800		// numero di punti in cui calcolare il disegno dei cerchi
#define THICK				1		// spessore linee spesse
#define COL_BCK				makecol(190, 190, 190) 	// colore background
#define COL_RETT			makecol(0, 0, 179)		// colore rettangoli
#define COL_SCR				makecol(0, 0, 0)		// colore scritte
#define COL_MDL				makecol(255, 0, 0)		// colore link
#define COL_MDL2			makecol(255, 204, 0)	// colore link 2
#define COL_VERT            makecol(0,0,0)			// colore base (sezione verticale)
#define COL_RIF				makecol(128, 128, 128)	// colore riferimenti

// par_control	
#define KP_ALPHA_DEF 		1 	// Valori di default delle costanti per i controllori
#define KD_ALPHA_DEF 		1 	// P = proporzionale, D = derivativo
#define KP_THETA_DEF 		1 	// su = swing up
#define KD_THETA_DEF 		1
#define KSU_DEF 			1
#define INCR_K				0.25 // incremento da tastiera 

//----------- tasks, in ordine di priorita`
// state_update
#define ID_STATE_UPDATE		10	// id task
#define PRIO_STATE_UPDATE	99	// priorita` task, 0-99
#define PERIOD_STATE_UPDATE	4	// periodo task in ms

// control
#define ID_CONTROL			300
#define PRIO_CONTROL		90
#define PERIOD_CONTROL		40

// compc
#define ID_COMPC			400
#define PRIO_COMPC			30
#define PERIOD_COMPC		20

// comboard
#define ID_COMBOARD			500
#define PRIO_COMBOARD		30
#define PERIOD_COMBOARD		20

// gui
#define ID_GUI				100
#define PRIO_GUI			20
#define FPS					60

// keys
#define ID_KEYS				200
#define PRIO_KEYS			10
#define PERIOD_KEYS			20

//----------- parametri scheda
#define CCR_MAX				5250 //PWM CCR 0-5250, 0 corrisponde a -6 Volt, 5250 a +6 Volt
#define CNT_MAX				4096 //ENC CNT 0-4096, 0 e 4096 corrispondono a  0 e 2*pi (posizione up per theta)

	
//----------- types, definizioni
// types per gui

typedef struct {
    int x;
    int y;
} Point; 

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
} TwoPoints;

typedef struct {
    float x;
    float y;
    float z;
} Vect;

typedef struct {
    float sin;
    float cos;
} AngleSinCos;

// types usati da piu` task

typedef struct {
    float alpha;		// angolo con asta orizzontale
	float alphadot;		// velocita` di alpha 
    float theta;		// angolo con asta verticale
	float thetadot;		// velocita` di theta
	float current;		// corrente motore
    float voltage;		// voltaggio motore
	int ccr;			// capture compare register (per settare duty cicle del pwm del motore)
	float enc_alpha;	// lettura encoder per l'angolo alpha
	float enc_theta;	// lettura encoder per l'angolo theta
} State;	// structure dello stato

typedef struct {
    float alpha;
    float theta;
} Ref;		// structure del riferimento

typedef struct{
	float alpha_kp;		// guadagno proporzionale controllore su alpha
	float alpha_kd;		// guadagno derivativo controllore su alpha
	float theta_kp;		// guadagno proporzionale controllore su theta
	float theta_kd;		// guadagno derivativo controllore su theta
	float ksu;			// guadagno del controllore di swing up
} Par_control;	// structure dei parametri di controllo

typedef struct {
    int lon;
    int lat;
} View; 		// structure della vista


/*
 * alla fine non l'ho usato
typedef struct{
	int brake;
	State state;
	Par_control par_control;
	Ref ref;
} Buffer;

// magari ci andrebbe messo swingup?
*/

#endif //CONDIVISO_H
