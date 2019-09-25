#ifndef SUPERQUADRICS_H
#define SUPERQUADRICS_H

#define PI 3.14159265358979323846

typedef struct {
	float x;
	float y;
	float z;
}summit;

float sign(float x);
float fexp(float x, float p);
summit func_eval(float a, float b, float c, float p, float q, float phi, float theta);
float** discretization(float a, float b, float a_p, float b_p, float m, float n);
summit** summit_building(float a, float b, float c, float p, float q, int m, int n, float** espace);

#endif
