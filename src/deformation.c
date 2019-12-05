#include <deformation.h>

summit taper(summit sum, float kx, float ky, float a3){
	float fact_x = kx / a3;
	float fact_y = ky / a3;

	summit sum_result;
	sum_result.x = ((fact_x * sum.z) + 1.f) * sum.x;
	sum_result.y = ((fact_y * sum.z) + 1.f) * sum.y;
	sum_result.z = sum.z;

	return sum_result;
}

summit bend(summit sum, float k, float alpha){
	float beta = atan(sum.y / sum.x);
	float gama = sum.z / k;
	float r = cos(alpha - beta) * sqrt(pow(sum.x, 2) + pow(sum.y, 2));
	float R = (1 / k) - cos(gama) * ((1 / k) - r);

	summit sum_result;
	sum_result.x = sum.x + (R - r) * cos(alpha);
	sum_result.y = sum.y + (R - r) * sin(alpha);
	sum_result.z = ((1 / k) - r) * sin(gama);

	return sum_result;	
}

summit twist(summit sum, float n, float a1){
	
	float theta = n*(PI+(sum.x/a1)*PI);
	
	summit sum_result;

	sum_result.x = sum.x;
	sum_result.y = sum.y*cos(theta)-sum.z*sin(theta);
	sum_result.z = sum.y*sin(theta)+sum.z*cos(theta);

	return sum_result;
}

int taper_forme(superquadrics forme){
 	if(forme.summits == NULL){
 		fprintf(stderr, "taper: invalid argument!\n");
		return -1;		
 	}

	float kx = forme.kx;
	float ky = forme.ky;
	float a3 = forme.a3;
	for(int i = 0; i <= forme.m; i++){
		for(int j = 0; j <= forme.n; j++){
			forme.summits[i][j] = taper(forme.summits[i][j], kx, ky, a3);
		}
	}

 	return 0;
}

int bend_forme(superquadrics forme){
 	if(forme.summits == NULL){
 		fprintf(stderr, "bend: invalid argument!\n");
		return -1;		
 	}

 	float k = forme.k;
 	float alpha = forme.alpha;
	for(int i = 0; i <= forme.m; i++){
		for(int j = 0; j <= forme.n; j++){		
			forme.summits[i][j] = bend(forme.summits[i][j], k, alpha);	
		}
	}

 	return 0;
}

int twist_forme(superquadrics forme){
 	if(forme.summits == NULL){
 		fprintf(stderr, "bend: invalid argument!\n");
		return -1;		
 	}

 	float n = forme.nt;
 	float a1 = forme.a1;
	for(int i = 0; i <= forme.m; i++){
		for(int j = 0; j <= forme.n; j++){		
			forme.summits[i][j] = twist(forme.summits[i][j], n, a1);	
		}
	}

 	return 0;
}

summit reverse_taper(summit sum, float kx, float ky, float a3){
	float fact_x = kx / a3;
	float fact_y = ky / a3;	

	summit sum_result;
	sum_result.x = sum.x / ((fact_x * sum.z) + 1.f);
	sum_result.y = sum.y / ((fact_y * sum.z) + 1.f);
	sum_result.z = sum.z;

	return sum_result;
}

int reverse_taper_forme(superquadrics forme){
 	if(forme.summits == NULL){
 		fprintf(stderr, "reverse_taper: invalid argument!\n");
		return -1;		
 	}

	float kx = forme.kx;
	float ky = forme.ky;
	float a3 = forme.a3;
	for(int i = 0; i <= forme.m; i++){
		for(int j = 0; j <= forme.n; j++){
			forme.summits[i][j] = reverse_taper(forme.summits[i][j], kx, ky, a3);
		}
	}

 	return 0;
}

int reverse_bend_forme(superquadrics forme){
 	if(forme.summits == NULL){
 		fprintf(stderr, "reverse_bend: invalid argument!\n");
		return -1;		
 	}

	for(int i = 0; i <= forme.m; i++){
		for(int j = 0; j <= forme.n; j++){

		}
	}

 	return 0;
}