#ifndef CONDIVISO_H
	#define CONDIVISO_H

#include <stdbool.h>
#include <pthread.h>
#include "rtwtypes.h" //conversioni matlab
#include "zero_crossing_types.h"
//#include "controller.h"

//----------- costanti, definizioni
// stato, _0 iniziale 
#define ALPHA_0				0
#define ALPHADOT_0			0
#define THETA_0				0
#define THETADOT_0			0
#define CURRENT_0			0
#define VOLTAGE_0			0
#define CCR_0				2625 // meta` del range 0-5250
#define CNT_ALPHA_0			0
#define CNT_THETA_0			0

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
#define KP_UP_ALPHA_DEF 	-2.23606801F 	// Valori di default delle costanti per i controllori
#define KP_UP_THETA_DEF 	-20.0269184F 	// UP = quando il pendolo e` su, DWON = quando il pendolo e` giu`
#define KD_UP_ALPHA_DEF 	-2.08667636F 	// P = proporzionale, D = derivativo
#define KD_UP_THETA_DEF 	-2.67355F
#define KP_DOWN_ALPHA_DEF	0.9F
#define KD_DOWN_ALPHA_DEF	0.0F
#define DPOLE_REF			0.990049839F
#define REF_GEN_NUM			{ 0.00995016098F, 0.0F }
#define REF_GEN_DEN			{ 1.0F, -0.990049839F }
//#define KSU_DEF 			1
#define INCR_K				0.15 // incremento da tastiera 

// dn
#define KICK_DEF			0U
#define DIST_DEF			0.0F
#define NOISE_DEF			{ 0.0F, 0.0F }
#define DELAY_DEF			0U

// par_dn
#define DIST_AMP_DEF		1
#define NOISE_AMP_DEF		0


//ref
#define ALPHA_REF			0
#define THETA_REF			0
#define SWINGUP_DEF			1


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
/* OLD
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
*/

/* OLD
typedef struct {
    float alpha;
    float theta;
} Ref;		// structure del riferimento
*/

/* OLD
typedef struct{
	float alpha_kp;		// guadagno proporzionale controllore su alpha
	float alpha_kd;		// guadagno derivativo controllore su alpha
	float theta_kp;		// guadagno proporzionale controllore su theta
	float theta_kd;		// guadagno derivativo controllore su theta
	float ksu;			// guadagno del controllore di swing up
} Par_control;	// structure dei parametri di controllo
*/

typedef struct {
    int lon;
    int lat;
} View; 		// structure della vista



//------ structure generate da Matlab
typedef struct {
    uint8_T kick;
    real32_T dist;
    real32_T noise[2];
    uint8_T delay;
} dn_t;// disturb and noise

typedef struct
{
    uint16_T CNT_alpha;
    uint16_T CNT_theta;
    uint16_T CCR;
} state_board_t;


typedef struct {
    real32_T alpha;
    real32_T theta;
    real32_T voltage;
} state_pc_t;

typedef struct {
    real32_T up_kp_alpha;
    real32_T up_kp_theta;
    real32_T up_kd_alpha;
    real32_T up_kd_theta;
    real32_T down_kp_alpha;
    real32_T down_kd_alpha;
    real32_T dpole_ref;
    real32_T ref_gen_num[2];
    real32_T ref_gen_den[2];
} par_ctrl_t;

typedef struct {
    real32_T dist_amp;
    real32_T noise_amp;
} par_dn_t;

typedef struct {
    real32_T alpha;
    real32_T theta;
    uint8_T swingup;
} ref_t;

typedef struct {
    real32_T Delay_DSTATE[4];            /* '<S7>/Delay' */
    real32_T DiscreteTimeIntegrator_DSTATE[4];/* '<S7>/Discrete-Time Integrator' */
    real32_T Delay_DSTATE_p;             /* '<S3>/Delay' */
    real32_T DiscreteStateSpace_DSTATE;  /* '<S3>/Discrete State-Space' */
} DW_fast_T;


// Block signals and states (default storage) for system '<S5>/ref_gen' 
typedef struct {
  real_T DiscreteTransferFcn_states;   // '<S8>/Discrete Transfer Fcn' 
  uint8_T DiscreteTransferFcn_icLoad; // '<S8>/Discrete Transfer Fcn' 
} DW_ref_gen_slow_T;


// Zero-crossing (trigger) state for system '<S5>/ref_gen'
typedef struct {
  ZCSigState DiscreteTransferFcn_Reset_ZCE;// '<S8>/Discrete Transfer Fcn'
} ZCE_ref_gen_slow_T;


typedef struct {
  DW_ref_gen_slow_T ref_gen;           /* '<S5>/ref_gen' */
  real_T Noise_generator_NextOutput;   /* '<S12>/Noise_generator' */
  real_T Noise_generator1_NextOutput;  /* '<S12>/Noise_generator1' */
  real32_T Delay_DSTATE[2];            /* '<S6>/Delay' */
  real32_T vel_estim_DSTATE[2];        /* '<S6>/vel_estim' */
  real32_T K[4];                       /* '<S3>/Hybrid_controller' */
  real32_T dist;                       /* '<S10>/Disturbance_generator' */
  real32_T volt;                       /* '<S3>/Hybrid_controller' */
  real32_T theta_ref;                  /* '<S3>/Hybrid_controller' */
  uint32_T RandSeed;                   /* '<S12>/Noise_generator' */
  uint32_T RandSeed_n;                 /* '<S12>/Noise_generator1' */
  uint16_T Delay_DSTATE_l[255];        /* '<S3>/Delay' */
  uint8_T is_active_c8_slow;           /* '<S10>/Disturbance_generator' */
  uint8_T is_c8_slow;                  /* '<S10>/Disturbance_generator' */
  uint8_T temporalCounter_i1;          /* '<S10>/Disturbance_generator' */
  uint8_T is_active_c5_slow;           /* '<S3>/Hybrid_controller' */
  uint8_T is_c5_slow;                  /* '<S3>/Hybrid_controller' */
  uint8_T is_Sliding_mode_controller;  /* '<S3>/Hybrid_controller' */
} DW_slow_T;

typedef struct {
  ZCE_ref_gen_slow_T ref_gen;          /* '<S5>/ref_gen' */
} PrevZCX_slow_T;



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
