//
// Foglio delle definizioni
//

#ifndef SIMUL_FURUTA_DEFINES_H
#define SIMUL_FURUTA_DEFINES_H

//Grafica
#define GRAFICA_WIN32       GFX_GDI
#define GRAFICA_LINUX       GFX_AUTODETECT_WINDOWED
#define wscreen             1024
#define hscreen             768
#define color_depth         32
#define dist                20
#define wrett1              400
#define L1_ASSO             133
#define L2_ASSO             100
#define L1_ALTO             100
#define L2_LATO             100
#define LX_GRID				180
#define LY_GRID				200
#define NUM_GRID			5
#define NUM_POINTS			800
#define THICK				1

//Tipi definiti da noi
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
	int x;
	int y;
	int z;
} Vect;

typedef struct {
	float sin;
	float cos;
}AngleSinCos;

typedef struct {
		float alpha;
		float theta;
		float lon;
		float lat;
		float bu;
}Par;



#endif //SIMUL_FURUTA_DEFINES_H
