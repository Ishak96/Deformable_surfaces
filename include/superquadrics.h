#ifndef SUPERQUADRICS_H
#define SUPERQUADRICS_H

#define PI 3.14159265358979323846
#define VAL  0.017453292

typedef struct {
	float x;
	float y;
	float z;
}summit;

typedef struct{
	float a1, a2, a3;
	float e1, e2;
	float tx, ty, tz;
	float angle1, angle2, angle3;
	float r0, r1;
	float kx, ky;
	float alpha, k;
	float nt;
	summit* summits;
	int m, n;
	int size;
	int** facade;
}superquadrics;

float sign(float x);
float abs_(float x);
float fexp(float x, float p);
int equals_summit(summit sum1, summit sum2);
int find_summit(summit* sum, int n, summit sum_find);
summit func_eval(float a, float b, float c, float e1, float e2, float phi, float theta, float r0, float r1);
void summit_building(float a, float b, float c, float e1, float e2, int m, int n, 
						 float r0, float r1, float a_p, float b_p, float a_t, float b_t,
						 superquadrics* forme);
superquadrics create_superquadrics(float a, float b, float c, float e1, float e2, int m, int n, 
									float r0, float r1, float a_p, float b_p, float a_t, float b_t);

#endif
