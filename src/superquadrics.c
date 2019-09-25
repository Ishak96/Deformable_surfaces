#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#include <superquadrics.h>

float sign(float x){
	return ( (x < 0) ? -1 : ( (x > 0) ? 1 : 0 ) );
}

float fexp(float x, float p){
	return ( sign(x) * (pow(abs(x), p)) );
}

summit func_eval(float a, float b, float c, float e1, float e2, float phi, float theta){
	summit coordinates;

	coordinates.x = a * (pow(cos(phi), e1)) * (pow(cos(theta), e2));
	coordinates.y = b * (pow(cos(phi), e1)) * (pow(sin(theta), e2));
	coordinates.z = c * (pow(sin(phi), e1));

	return coordinates;
}

float** discretization(float a, float b, float a_p, float b_p, float m, float n){
	float** values;

	values = malloc(2 * sizeof(float*));
	values[0] = malloc(m * sizeof(float));
	values[1] = malloc(n * sizeof(float));

	for(int i = 0; i <= m; i++){
		values[0][i] = a + (i * (b - a)) / m;
	}

	for(int j = 0; j <= n; j++){
		values[1][j] = a_p + (j * (b_p - a_p)) / n;
	}

	return values;
}

summit** summit_building(float a, float b, float c, float p, float q, int m, int n, float** espace){
	summit** sum;

	sum = malloc(m * sizeof(summit*));
	for(int i = 0; i <= m; i++){
		sum[i] = malloc(n * sizeof(summit));
	}

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			sum[i][j] = func_eval(a, b, c, p, q, espace[0][i], espace[1][j]);
		}
	}

	return sum;
}