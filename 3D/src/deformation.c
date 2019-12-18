#include <deformation.h>

SUMMIT taper(SUMMIT sum, float kx, float ky, float a3){
	float fact_x = kx / a3;
	float fact_y = ky / a3;

	SUMMIT sum_result;

	sum_result.x = ((fact_x * sum.z) + 1) * sum.x;
	sum_result.y = ((fact_y * sum.z) + 1) * sum.y;
	sum_result.z = sum.z;

	return sum_result;
}

SUMMIT bend(SUMMIT sum, float k, float alpha){
	float beta;
	float ro;
	float gama;
	SUMMIT sum_result;
	if(fabs(k) > DELTA){
		ro = 1. / k;

		if(fabs(sum.x) < DELTA)
			beta = sign(sum.y) * PI / 2;
		else
			beta = atan2(sum.y, sum.x);

		gama = sum.z * k;

		float r = cos(alpha - beta) * sqrt(sum.x*sum.x + sum.y*sum.y);
		float R = ro - cos(gama) * (ro - r);

		sum_result.x = sum.x + cos(alpha) * (R - r);
		sum_result.y = sum.y + sin(alpha) * (R - r);
		sum_result.z = sin(gama) * (ro - r);
	}

	return sum_result;	
}

SUMMIT twist(SUMMIT sum, float nt, float a1){
	float theta = nt * (PI + (sum.x / a1) * PI);

	SUMMIT sum_result;

	sum_result.x = sum.x;
	sum_result.y = sum.y * cos(theta) - sum.z * sin(theta);
	sum_result.z = sum.y * sin(theta) + sum.z * cos(theta);

	return sum_result;
}

int taper_SUPERQUADRIC(SUPERQUADRIC superquadric){
 	if(superquadric.summits == NULL){
 		fprintf(stderr, "taper: invalid argument!\n");
		return -1;		
 	}

 	int size_summits = superquadric.size_summits;

	float kx = superquadric.parameters.kx;
	float ky = superquadric.parameters.ky;
	float a3 = superquadric.parameters.a3;

	for(int i = 0; i < size_summits; i++)
		superquadric.summits[i] = taper(superquadric.summits[i], kx, ky, a3);

 	return 0;
}

int bend_SUPERQUADRIC(SUPERQUADRIC superquadric){
 	if(superquadric.summits == NULL){
 		fprintf(stderr, "taper: invalid argument!\n");
		return -1;		
 	}

	int size_summits = superquadric.size_summits;
	float k = superquadric.parameters.k;
	float alpha = superquadric.parameters.alpha;
	
	for(int i = 0; i < size_summits; i++)
		superquadric.summits[i] = bend(superquadric.summits[i], k, alpha);
 	
 	return 0;
}

int twist_SUPERQUADRIC(SUPERQUADRIC superquadric){
 	if(superquadric.summits == NULL){
 		fprintf(stderr, "taper: invalid argument!\n");
		return -1;		
 	}

 	int size_summits = superquadric.size_summits;

 	float nt = superquadric.parameters.nt;
 	float a1 = superquadric.parameters.a1;

 	for(int i = 0; i < size_summits; i++)
 		superquadric.summits[i] = twist(superquadric.summits[i], nt, a1);
 	return 0;
}

SUMMIT reverse_taper(SUMMIT sum, float kx, float ky, float a3){
	float fact_x = kx / a3;
	float fact_y = ky / a3;	

	SUMMIT sum_result;

	sum_result.x = sum.x / ((fact_x * sum.z) + 1.f);
	sum_result.y = sum.y / ((fact_y * sum.z) + 1.f);
	sum_result.z = sum.z;	

	return sum_result;
}

SUMMIT reverse_bend(SUMMIT sum, float k, float alpha){
	float beta;
	float ro;
	float gama;
	SUMMIT sum_result = sum;
	
	if(fabs(k) > DELTA){
		
		ro = 1./k;

		if(fabs(sum.x) < DELTA)
			beta = sign(sum.y) * PI / 2;
		else
			beta = atan2(sum.y, sum.x);

		float R = cos(alpha - beta) * sqrt(pow(sum.x, 2) + pow(sum.y, 2));
		float r = ro - sqrt(pow(sum.z, 2) + pow((ro - R), 2));

		if(fabs(ro - R) < DELTA)
			gama = sign(sum.z) * PI / 2;
		else
			gama = atan2(sum.z, ro - R);

		sum_result.x = sum.x - cos(alpha) * (R - r);
		sum_result.y = sum.y - sin(alpha) * (R - r);
		sum_result.z = ro * gama;
	}

	return sum_result;	
}

SUMMIT reverse_twist(SUMMIT sum, float nt, float a1){

	SUMMIT sum_result;

	return sum_result;
}

int reverse_taper_SUPERQUADRIC(SUPERQUADRIC superquadric){
 	if(superquadric.summits == NULL){
 		fprintf(stderr, "reverse_taper_SUPERQUADRIC: invalid argument!\n");
		return -1;		
 	}

 	int size_summits = superquadric.size_summits;

	float kx = superquadric.parameters.kx;
	float ky = superquadric.parameters.ky;
	float a3 = superquadric.parameters.a3;

	for(int i = 0; i < size_summits; i++)
		superquadric.summits[i] = reverse_taper(superquadric.summits[i], kx, ky, a3);

 	return 0;
}

int reverse_bend_SUPERQUADRIC(SUPERQUADRIC superquadric){
 	if(superquadric.summits == NULL){
 		fprintf(stderr, "reverse_bend_SUPERQUADRIC: invalid argument!\n");
		return -1;		
 	}

	int size_summits = superquadric.size_summits;
	float k = superquadric.parameters.k;
	float alpha = superquadric.parameters.alpha;

	for(int i = 0; i < size_summits; i++)
		superquadric.summits[i] = reverse_bend(superquadric.summits[i], k, alpha);
 	
 	return 0;
}

int reverse_twist_SUPERQUADRIC(SUPERQUADRIC superquadric){
 	if(superquadric.summits == NULL){
 		fprintf(stderr, "reverse_twist_SUPERQUADRIC: invalid argument!\n");
		return -1;		
 	}	

 	return 0;
}