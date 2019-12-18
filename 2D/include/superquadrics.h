#ifndef SUPERQUADRICS_H
#define SUPERQUADRICS_H

#define PI 				3.14159265358979323846
#define VAL  			0.017453292
#define DELTA 			0.00001
#define NB_COLS_FACADES 5
#define PHI 			PI / 2
#define THETA 			PI

typedef struct {
	float x;
	float y;
}SUMMIT;

typedef struct{
	float a1, a2;
	float e;
	float tx, ty;
	float angle;
	float ky;
	float k;
	float nt;
}PARAMETERS;

typedef struct{
	PARAMETERS parameters;
	SUMMIT* summits;
	int size_summits;
}SUPERQUADRIC;

#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#include <util.h>
#include <superquadrics.h>

float sign(float x);

float abs_(float x);

float fexp(float x, float p);

int equals_summit(SUMMIT sum1, SUMMIT sum2);

SUMMIT func_eval(float a, float b, float e, float phi);

SUMMIT create_SUMMIT(PARAMETERS parameters, float phi);

float SUMMIT_distance(SUMMIT sum1, SUMMIT sum2);

void summit_building(SUPERQUADRIC* superquadric, float phi[]);

SUPERQUADRIC create_superquadrics(float a, float b, float e, int length, float phi[]);

void destroy_superquadrics(SUPERQUADRIC* superquadric);
#endif
