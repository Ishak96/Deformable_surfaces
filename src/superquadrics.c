#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#include <superquadrics.h>

float sign(float x){
	return ( (x < 0) ? -1 : ( (x > 0) ? 1 : 0 ) );
}

float abs_(float x){
	return sign(x) * x;
}

float fexp(float x, float p){
	return ( sign(x) * (pow(abs_(x), p)) );
}

int equals_summit(summit sum1, summit sum2){
	return sum1.x == sum2.x 
			&& sum1.y == sum2.y 
			&& sum1.z == sum2.z;
}

int find_summit(summit* sum, int n, summit sum_find){
	int find = 0;
	
	for(int i = 0; i < n && !find; i++){
		summit sum_at = sum[i];
		find = equals_summit(sum_find, sum_at);
	}

	return find;
}

summit func_eval(float a, float b, float c, float e1, float e2, float phi, float theta, float r0, float r1){
	summit coordinates;

	coordinates.x = a * (r0 + r1 * fexp(cos(phi), e1)) * (fexp(cos(theta), e2));
	coordinates.y = b * (r0 + r1 * fexp(cos(phi), e1)) * (fexp(sin(theta), e2));
	coordinates.z = c * (r1 * fexp(sin(phi), e1));

	return coordinates;
}

void summit_building(float a, float b, float c, float e1, float e2, int m, int n, 
						 float r0, float r1, float a_p, float b_p, float a_t, float b_t,
						 superquadrics* forme){
	int nb_sum = 0;
	
	forme->summits = (summit *)malloc((m+1) * (n+1) * sizeof(summit));

	for(int i = 0; i <= m; i++){
		for(int j = 0; j <= n; j++){
			float phi = a_p + (i * (b_p - a_p)) / m;
			float theta = a_t + (j * (b_t - a_t)) / n;

			summit sum_add = func_eval(a, b, c, e1, e2, phi, theta, r0, r1);
			if(!find_summit(forme->summits, nb_sum, sum_add)){
				forme->summits[i*(n+1)+j] = sum_add;
				nb_sum++;
			}
		}
	}

	forme->size = (m*n)*2;
	forme->facade = malloc(forme->size * sizeof(int *));
	for(int i = 0; i <= forme->size; i++)
		forme->facade[i] = malloc(3*sizeof(int));

	int facade_index = 0;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			forme->facade[facade_index][0] = i*(n+1)+j;
			forme->facade[facade_index][1] = (i+1)*(n+1)+j;
			forme->facade[facade_index][2] = (i+1)*(n+1)+(j+1);
			facade_index++;
			
			forme->facade[facade_index][0] = i*(n+1)+j;
			forme->facade[facade_index][1] = (i+1)*(n+1)+(j+1);
			forme->facade[facade_index][2] = i*(n+1)+(j+1);
			facade_index++;
		}
	}
}

superquadrics create_superquadrics(float a, float b, float c, float e1, float e2, int m, int n, 
									float r0, float r1, float a_p, float b_p, float a_t, float b_t){
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