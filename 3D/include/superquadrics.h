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
	float z;
}SUMMIT;

typedef struct{
	float a1, a2, a3;
	float e1, e2;
	float tx, ty, tz;
	float angle1, angle2, angle3;
	float r0, r1;
	float kx, ky;
	float alpha, k;
	float nt;
}PARAMETERS;

typedef struct{
	PARAMETERS parameters;
	SUMMIT* summits;
	int** facades;
	int parallels,meridians;
	int size_summits,size_facades;
}SUPERQUADRIC;

float sign(float x);
float abs_(float x);
float fexp(float x, float p);

int equals_summit(SUMMIT sum1, SUMMIT sum2);

SUMMIT func_eval(float a, float b, float c, float e1, float e2,
				 float phi, float theta);

SUMMIT create_SUMMIT(PARAMETERS parameters, float phi, float theta);

float SUMMIT_distance(SUMMIT sum1, SUMMIT sum2);

void summit_building(SUPERQUADRIC* superquadric, float phi[], float theta[]);

void facade_building(SUPERQUADRIC* superquadric);

SUPERQUADRIC create_superquadrics(float a, float b, float c, float e1, float e2, 
								  int parallels, int meridians,
								  float phi[], float theta[]);

void destroy_superquadrics(SUPERQUADRIC* superquadric);

#endif
