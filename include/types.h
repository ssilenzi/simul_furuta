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

#endif //SIMUL_FURUTA_TYPES_H
