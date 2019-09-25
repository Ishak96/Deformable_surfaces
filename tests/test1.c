#include<stdio.h>
#include<stdlib.h>

#include<superquadrics.h>

int main(int argc, char** argv) {

	int m = 1000;
	int n = 1000;
	float a = 4;
	float b = 2;
	float c = 1;
	float p = 1;
	float q = 1;
	
	float** values = discretization(-PI / 2, PI / 2, -PI, PI, m, n);

	for(int i = 0; i <= m; i++){
		printf("%f || ", values[0][i]);
	}
	
	printf("\n\t\t\t\t\t\t\t______________________________________________________________\n");

	for(int i = 0; i <= n; i++){
		printf("%f || ", values[1][i]);
	}

	printf("\n\n summit building :");
	summit** sum = summit_building(a, b, c, p, q, m, n, values);

	for(int i = 0; i <= m; i++){
		for(int j = 0; j <= n; j++){
			printf("for{phi = %f, theta = %f} => {x = %f, y = %f, z = % f}\n", values[0][i], values[1][j], sum[i][j].x, sum[i][j].y, sum[i][j].z);
		}
	}

	return 0;
}
