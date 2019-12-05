#ifndef SUPERQUADRICS_H
#define SUPERQUADRICS_H

#define PI 3.14159265358979323846
#define VAL  0.017453292

typedef struct {
	double x;
	double y;
	double z;
}summit;

typedef struct{
	float a1, a2, a3;
	float e1, e2;
	float tx, ty, tz;
	float abgle1, angle2, angle3;
	float r0, r1;
	float kx, ky;
	float alpha, k;
	float nt;
	summit** summits;
	float m, n;
}superquadrics;

double sign(double x);
double abs_(double x);
double fexp(double x, double p);
summit func_eval(double a, double b, double c, double e1, double e2, double phi, double theta, double r0, double r1);
double** discretization(double a, double b, double a_p, double b_p, double m, double n);
summit** summit_building(double a, double b, double c, double p, double q, double m, double n, 
						 double** espace, double r0, double r1);

#endif
