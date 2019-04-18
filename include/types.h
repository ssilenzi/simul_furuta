//
// Created by simone on 4/17/19.
//

#ifndef SIMUL_FURUTA_TYPES_H
#define SIMUL_FURUTA_TYPES_H

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
} AngleSinCos;

typedef struct {
    float alpha;
    float theta;
    float lon;
    float lat;
    float bu;
} Par;

#endif //SIMUL_FURUTA_TYPES_H
