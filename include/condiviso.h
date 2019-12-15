#ifndef CONDIVISO_H
	#define CONDIVISO_H

#include <stdbool.h>
#include <pthread.h>

//----------- costanti, definizioni
// stato
#define ALPHA_0             0
#define ALPHADOT_0			0
#define THETA_0             0
#define THETADOT_0			0
#define CURRENT_0			0
#define VOLTAGE_0			0
#define CCR_0				0
#define ENC_ALPHA_0			0
#define ENC_THETA_0			0

// view
#define LON_0               45
#define LAT_0               35
#define LAT_MAX             90
#define INCR_ANG            5

// gui
#define GRAFICA_LINUX       GFX_AUTODETECT_WINDOWED
#define GRAFICA_WIN32       GFX_GDI
#define WSCREEN             1024
#define HSCREEN             768
#define COLOR_DEPTH         32
#define DIST                20
#define WRETT1              400
#define L1_ASSON			133
#define L2_ASSON			100
#define L1_ALTO             100
#define L2_LATO             100
#define LX_GRID				180
#define LY_GRID				200
#define NUM_GRID			5
#define NUM_POINTS			800
#define THICK				1
#define COL_BCK				makecol(190, 190, 190)
#define COL_RETT			makecol(0, 0, 179)
#define COL_SCR				makecol(0, 0, 0)
#define COL_MDL				makecol(255, 0, 0)
#define COL_MDL2			makecol(255, 204, 0)
#define COL_VERT            makecol(0,0,0)
#define COL_RIF				makecol(128, 128, 128)

// par_control	
#define KP_ALPHA_DEF 		1 // Valori di default delle costanti per i controllori
#define KD_ALPHA_DEF 		1 // P = proporzionale, D = derivativo
#define KP_THETA_DEF 		1 // su = swing up
#define KD_THETA_DEF 		1
#define KSU_DEF 			1
#define INCR_K				1 // incremento da tastiera 

//----------- tasks, in ordine di priorita`
// state_update
#define ID_STATE_UPDATE		10
#define PRIO_STATE_UPDATE	99
#define PERIOD_STATE_UPDATE	4

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
	float ccr;			// capture compare register (per settare duty cicle del pwm del motore)
	float enc_alpha;	// lettura encoder per l'angolo alpha
	float enc_theta;	// lettura encoder per l'angolo theta
} State;

typedef struct {
    float alpha;
    float theta;
} Ref;

typedef struct{
	float alpha_kp;		// guadagno proporzionale controllore su alpha
	float alpha_kd;		// guadagno derivativo controllore su alpha
	float theta_kp;		// guadagno proporzionale controllore su theta
	float theta_kd;		// guadagno derivativo controllore su theta
	float ksu;			// guadagno del controllore di swing up
} Par_control;


typedef struct {
    int lon;
    int lat;
} View;

typedef struct{
	int brake;
	State state;
	Par_control par_control;
	Ref ref;
} Buffer;




#endif //CONDIVISO_H
