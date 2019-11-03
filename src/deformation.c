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

 	return 0;
}

int reverse_bend(superquadrics forme){
 	if(forme.summits == NULL || forme.parameters == NULL){
 		fprintf(stderr, "reverse_bend: invalid argument!\n");
		return -1;		
 	}

 	return 0;
}