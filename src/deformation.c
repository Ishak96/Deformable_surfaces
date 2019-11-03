#include <deformation.h>

int taper(float** cloud, int size, float kx, float ky){
 	if(cloud == NULL){
 		fprintf(stderr, "taper: invalid argument!\n");
		return -1;		
 	}

 	return 0;
}

int reverse_taper(float** cloud, int size, float kx, float ky){
 	if(cloud == NULL){
 		fprintf(stderr, "reverse_taper: invalid argument!\n");
		return -1;		
 	}

 	return 0;
}

int bend(float** cloud, int size, float k, float alpha){
 	if(cloud == NULL){
 		fprintf(stderr, "bend: invalid argument!\n");
		return -1;		
 	}

 	return 0;
}

int reverse_bend(float** cloud, int size, float k, float alpha){
 	if(cloud == NULL){
 		fprintf(stderr, "reverse_bend: invalid argument!\n");
		return -1;		
 	}

 	return 0;
}