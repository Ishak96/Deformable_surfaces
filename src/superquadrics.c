#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#include <superquadrics.h>

double sign(double x){
	return ( (x < 0) ? -1 : ( (x > 0) ? 1 : 0 ) );
}

double abs_(double x){
	return sign(x) * x;
}

double fexp(double x, double p){
	return ( sign(x) * (pow(abs_(x), p)) );
}

summit func_eval(double a, double b, double c, double e1, double e2, double phi, double theta, double r0, double r1){
	summit coordinates;

	coordinates.x = a * (r0 + r1 * fexp(cos(phi), e1)) * (fexp(cos(theta), e2));
	coordinates.y = b * (r0 + r1 * fexp(cos(phi), e1)) * (fexp(sin(theta), e2));
	coordinates.z = c * (r1 * fexp(sin(phi), e1));

	return coordinates;
}

summit** summit_building(double a, double b, double c, double p, double q, double m, double n, 
						 double r0, double r1, double a_p, double b_p, double a_t, double b_t){
	summit** sum;

	sum = malloc((m+1) * sizeof(summit*));
	for(int i = 0; i <= m; i++){
		sum[i] = malloc((n+1) * sizeof(summit));
	}

	for(int i = 0; i <= m; i++){
		for(int j = 0; j <= n; j++){
			float phi = a_p + ((double)i * (b_p - a_p)) / m;
			float theta = a_t + ((double)j * (b_t - a_t)) / n;
			sum[i][j] = func_eval(a, b, c, p, q, phi, theta, r0, r1);
		}
	}

	return sum;
}