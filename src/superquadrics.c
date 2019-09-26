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

summit func_eval(double a, double b, double c, double e1, double e2, double phi, double theta){
	summit coordinates;

	coordinates.x = a * (fexp(cos(phi), e1)) * (fexp(cos(theta), e2));
	coordinates.y = b * (fexp(cos(phi), e1)) * (fexp(sin(theta), e2));
	coordinates.z = c * (fexp(sin(phi), e1));

	return coordinates;
}

double** discretization(double a, double b, double a_p, double b_p, double m, double n){
	double** values;

	values = malloc(2 * sizeof(double*));
	values[0] = malloc((m+1) * sizeof(double));
	values[1] = malloc((n+1) * sizeof(double));

	for(int i = 0; i <= m; i++){
		values[0][i] = a + ((double)i * (b - a)) / m;
	}

	for(int j = 0; j <= n; j++){
		values[1][j] = a_p + ((double)j * (b_p - a_p)) / n;
	}

	return values;
}

summit** summit_building(double a, double b, double c, double p, double q, double m, double n, double** espace){
	summit** sum;

	sum = malloc((m+1) * sizeof(summit*));
	for(int i = 0; i <= m; i++){
		sum[i] = malloc((n+1) * sizeof(summit));
	}

	for(int i = 0; i <= m; i++){
		for(int j = 0; j <= n; j++){
			sum[i][j] = func_eval(a, b, c, p, q, espace[0][i], espace[1][j]);
		}
	}

	return sum;
}