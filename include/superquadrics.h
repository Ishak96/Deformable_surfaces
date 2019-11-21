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
	float parameters[16];
	summit** summits;
	float m;
	float n;
}superquadrics;

double sign(double x);
double abs_(double x);
double fexp(double x, double p);
summit func_eval(double a, double b, double c, double e1, double e2, double phi, double theta, double r0, double r1);
double** discretization(double a, double b, double a_p, double b_p, double m, double n);
summit** summit_building(double a, double b, double c, double p, double q, double m, double n, 
						 double** espace, double r0, double r1);

#endif
