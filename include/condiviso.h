#ifndef CONDIVISO_H
#define CONDIVISO_H

#include <stdbool.h>
#include <pthread.h>


//----------- costanti, definizioni
// stato
#define ALPHA_0             0
#define THETA_0             0

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


//----------- tasks
// state_update
#define ID_STATE_UPDATE		10
#define PRIO_STATE_UPDATE	60
#define PERIOD_STATE_UPDATE	20
	
// gui
#define FPS					40
#define ID_GUI				100
#define PRIO_GUI			20


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

typedef struct {
    float alpha;
    float theta;
    float I;
} State;

typedef struct {
    float alpha;
    float theta;
    float Kp;
    float Ki;
    float Kd;
} Ref;

typedef struct {
    int lon;
    int lat;
} View;


#endif //CONDIVISO_H
