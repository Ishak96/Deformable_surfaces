#include<stdio.h>
#include<stdlib.h>
#include <math.h>

#include<superquadrics.h>

int main(int argc, char** argv) {

	double a = 2;

	double phi = -1.570796;
	double theta = -2.513274;
	double e1 = 2;
	double e2 = 2;
	double x, ret;

	x = 60.0;
	ret = cos( x*VAL );

	printf("abs(phi) = %f\n", abs_(phi));
	printf("cos(phi) = %f\n", cos(phi*VAL));
	printf("(pow(cos(phi), e1)) = %f\n", pow(cos(phi*VAL), e1));
	printf("(pow(cos(theta), e2)) = %f\n", pow(cos(theta*VAL), e2));
	printf("a * (pow(cos(phi), e1)) * (pow(cos(theta), e2)) = %f\n", a * (pow(cos(phi*VAL), e1)) * (pow(cos(theta*VAL), e2)));

	printf("The cosine of %lf is %lf degrees\n", x, ret);

	return 0;
}
