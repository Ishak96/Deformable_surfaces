#include <deformation.h>

int taper(superquadrics forme){
 	if(forme.summits == NULL || forme.parameters == NULL){
 		fprintf(stderr, "taper: invalid argument!\n");
		return -1;		
 	}

	float fact_x = forme.parameters[11] / forme.parameters[10];
	float fact_y = forme.parameters[12] / forme.parameters[10];
	for(int i = 0; i <= forme.m; i++){
		for(int j = 0; j <= forme.n; j++){
			float x = forme.summits[i][j].x;
			float y = forme.summits[i][j].y;
			float z = forme.summits[i][j].z;

			forme.summits[i][j].x = ((fact_x * z) + 1.f) * x;
			forme.summits[i][j].y = ((fact_y * z) + 1.f) * y;
			forme.summits[i][j].z = z;
		}
	}

 	return 0;
}

int reverse_taper(superquadrics forme){
 	if(forme.summits == NULL || forme.parameters == NULL){
 		fprintf(stderr, "reverse_taper: invalid argument!\n");
		return -1;		
 	}

	float fact_x = forme.parameters[11] / forme.parameters[10];
	float fact_y = forme.parameters[12] / forme.parameters[10];
	for(int i = 0; i <= forme.m; i++){
		for(int j = 0; j <= forme.n; j++){
			float x = forme.summits[i][j].x;
			float y = forme.summits[i][j].y;
			float z = forme.summits[i][j].z;

			forme.summits[i][j].x = x / ((fact_x * z) + 1.f);
			forme.summits[i][j].y = y / ((fact_y * z) + 1.f);
			forme.summits[i][j].z = z;
		}
	}

 	return 0;
}

int bend(superquadrics forme){
 	if(forme.summits == NULL || forme.parameters == NULL){
 		fprintf(stderr, "bend: invalid argument!\n");
		return -1;		
 	}

	float k = forme.parameters[13];
	float alpha = forme.parameters[14];
	float r, lamda, R;
	for(int i = 0; i <= forme.m; i++){
		for(int j = 0; j <= forme.n; j++){
			float x = forme.summits[i][j].x;
			float y = forme.summits[i][j].y;
			float z = forme.summits[i][j].z;

			r = cos(alpha - atan(y / x)) * sqrt(pow(x, 2) + pow(y, 2));
			lamda = z * k;
			R = pow(k, -1) - cos(lamda) * (pow(k, -1) - r);

			forme.summits[i][j].x = x + (cos(alpha) * (R - r));
			forme.summits[i][j].y = y + (sin(alpha) * (R - r));
			forme.summits[i][j].z = sin(lamda) * (pow(k, -1) - r);
		}
	}

 	return 0;
}

int reverse_bend(superquadrics forme){
 	if(forme.summits == NULL || forme.parameters == NULL){
 		fprintf(stderr, "reverse_bend: invalid argument!\n");
		return -1;		
 	}

 	float k = forme.parameters[13];
	float alpha = forme.parameters[14];
	float r, lamda, R;
	for(int i = 0; i <= forme.m; i++){
		for(int j = 0; j <= forme.n; j++){
			float x = forme.summits[i][j].x;
			float y = forme.summits[i][j].y;
			float z = forme.summits[i][j].z;

			R = (x == 0) ? cos(alpha) * sqrt((y*y)): cos(alpha - atan(y / x)) * sqrt((x*x) + (y*y));
			float value = (k == 0) ? -R : (1 / k) - R;
			lamda = (value == 0) ? 0.f : atan(z / value);
			r = (k == 0) ? -sqrt((z*z) + (value*value)) : (1 / k) - sqrt((z*z) + (value*value));

			forme.summits[i][j].x = x - cos(alpha) * (R - r);
			forme.summits[i][j].y = y - sin(alpha) * (R - r);
			forme.summits[i][j].z = (k == 0) ? 0 : (1 / k) * lamda;
		}
	}

 	return 0;
}