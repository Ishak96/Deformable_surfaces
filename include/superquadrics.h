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
	float angle1, angle2, angle3;
	float r0, r1;
	float kx, ky;
	float alpha, k;
	float nt;
	summit* summits;
	int m, n;
	int size;
}superquadrics;

double sign(double x);
double abs_(double x);
double fexp(double x, double p);
int double_equals(double a1, double a2);
int equals_summit(summit sum1, summit sum2);
int find_summit(summit* sum, int i, int j, int n, summit sum_find);
summit func_eval(double a, double b, double c, double e1, double e2, double phi, double theta, double r0, double r1);
void summit_building(double a, double b, double c, double e1, double e2, int m, int n, 
						 double r0, double r1, double a_p, double b_p, double a_t, double b_t,
						 superquadrics* forme);
superquadrics create_superquadrics(double a, double b, double c, double e1, double e2, int m, int n, 
									double r0, double r1, double a_p, double b_p, double a_t, double b_t);

#endif
