#ifndef SUPERQUADRICS_H
#define SUPERQUADRICS_H

#define PI 3.14159265358979323846
#define VAL  0.017453292

typedef struct {
	double x;
	double y;
	double z;
}summit;

double sign(double x);
double abs_(double x);
double fexp(double x, double p);
summit func_eval(double a, double b, double c, double p, double q, double phi, double theta);
double** discretization(double a, double b, double a_p, double b_p, double m, double n);
summit** summit_building(double a, double b, double c, double p, double q, double m, double n, double** espace);

#endif
