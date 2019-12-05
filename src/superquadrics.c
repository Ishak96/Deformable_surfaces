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

int double_equals(double a1, double a2){
	return a1 == a2;
}

int equals_summit(summit sum1, summit sum2){
	return double_equals(sum1.x, sum2.x) 
			&& double_equals(sum1.y, sum2.y) 
			&& double_equals(sum1.z, sum2.z);
}

int find_summit(summit* sum, int i, int j, int n, summit sum_find){
	int find = 0;
	
	for(int temp_i = 0; temp_i < i && !find; temp_i++){
		for(int temp_j = 0; temp_j < j && !find; temp_j++){
			summit sum_at = sum[temp_i*n+temp_j];
			find = equals_summit(sum_find, sum_at);
		}
	}

	return find;
}

summit func_eval(double a, double b, double c, double e1, double e2, double phi, double theta, double r0, double r1){
	summit coordinates;

	coordinates.x = a * (r0 + r1 * fexp(cos(phi), e1)) * (fexp(cos(theta), e2));
	coordinates.y = b * (r0 + r1 * fexp(cos(phi), e1)) * (fexp(sin(theta), e2));
	coordinates.z = c * (r1 * fexp(sin(phi), e1));

	return coordinates;
}

void summit_building(double a, double b, double c, double e1, double e2, int m, int n, 
						 double r0, double r1, double a_p, double b_p, double a_t, double b_t,
						 superquadrics* forme){
	int nb_sum = 0;
	int size = (m+1) * (n+1);
	
	forme->summits = malloc(size * sizeof(summit));

	for(int i = 0; i <= m; i++){
		for(int j = 0; j <= n; j++){
			float phi = a_p + ((double)i * (b_p - a_p)) / m;
			float theta = a_t + ((double)j * (b_t - a_t)) / n;

			summit sum_add = func_eval(a, b, c, e1, e2, phi, theta, r0, r1);
			forme->summits[i*(n+1)+j] = sum_add;
			nb_sum++;
		}
	}

	forme->size = nb_sum;
}

superquadrics create_superquadrics(double a, double b, double c, double e1, double e2, int m, int n, 
									double r0, double r1, double a_p, double b_p, double a_t, double b_t){
	superquadrics forme;

	forme.a1 = a;
	forme.a2 = b;
	forme.a3 = c;
	forme.e1 = e1;
	forme.e2 = e2;
	forme.r0 = r0;
	forme.r1 = r1;
	forme.m = m;
	forme.n = n;
	summit_building(a, b, c, e1, e2, m, n, r0, r1, a_p, b_p, a_t, b_t, &forme);


	return forme;
}