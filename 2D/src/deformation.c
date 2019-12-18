#include <deformation.h>

SUMMIT taper(SUMMIT sum, float ky, float a1){
	float fact_y = ky / a1;

	SUMMIT sum_result;

	sum_result.x = sum.x;
	sum_result.y = ((fact_y * sum.x) + 1) * sum.y;

	return sum_result;
}

SUMMIT bend(SUMMIT sum, float k){
	float ro;
	float gama;
	SUMMIT sum_result = sum;
	if(fabs(k) > DELTA){
		ro = 1. / k;

		gama = sum.x * k;

		sum_result.x = sin(gama) * (ro - sum.y);
		sum_result.y = ro - cos(gama) * (ro - sum.y);
	}

	return sum_result;	
}

SUMMIT twist(SUMMIT sum, float nt, float a1){
	float theta = nt * (PI + (sum.x / a1) * PI);

	SUMMIT sum_result;

	sum_result.x = sum.x;
	sum_result.y = sum.y * cos(theta);

	return sum_result;
}

int taper_SUPERQUADRIC(SUPERQUADRIC superquadric){
 	if(superquadric.summits == NULL){
 		fprintf(stderr, "taper: invalid argument!\n");
		return -1;		
 	}

 	int size_summits = superquadric.size_summits;

	float ky = superquadric.parameters.ky;
	float a1 = superquadric.parameters.a1;

	for(int i = 0; i < size_summits; i++)
		superquadric.summits[i] = taper(superquadric.summits[i], ky, a1);

 	return 0;
}

int bend_SUPERQUADRIC(SUPERQUADRIC superquadric){
 	if(superquadric.summits == NULL){
 		fprintf(stderr, "taper: invalid argument!\n");
		return -1;		
 	}

	int size_summits = superquadric.size_summits;
	
	float k = superquadric.parameters.k;

	for(int i = 0; i < size_summits; i++)
		superquadric.summits[i] = bend(superquadric.summits[i], k);
 	
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

SUMMIT reverse_taper(SUMMIT sum, float ky, float a1){
	float fact_y = ky / a1;	

	SUMMIT sum_result;

	sum_result.x = sum.x;
	sum_result.y = sum.y / ((fact_y * sum.x) + 1.f);

	return sum_result;
}

SUMMIT reverse_bend(SUMMIT sum, float k){
	float ro;
	float gama;
	SUMMIT sum_result;

	if(fabs(k) > DELTA){
		
		ro = 1./k;

		gama = sum.x * k;

		sum_result.x = sum.x * ro;
		sum_result.y = ro + (sum.y - ro) / (cos(gama));
	}

	return sum_result;	
}

int reverse_taper_SUPERQUADRIC(SUPERQUADRIC superquadric){
 	if(superquadric.summits == NULL){
 		fprintf(stderr, "reverse_taper_SUPERQUADRIC: invalid argument!\n");
		return -1;		
 	}

 	int size_summits = superquadric.size_summits;

	float ky = superquadric.parameters.ky;
	float a1 = superquadric.parameters.a1;

	for(int i = 0; i < size_summits; i++)
		superquadric.summits[i] = reverse_taper(superquadric.summits[i], ky, a1);

 	return 0;
}

int reverse_bend_SUPERQUADRIC(SUPERQUADRIC superquadric){
 	if(superquadric.summits == NULL){
 		fprintf(stderr, "reverse_bend_SUPERQUADRIC: invalid argument!\n");
		return -1;		
 	}

	int size_summits = superquadric.size_summits;
	
	float k = superquadric.parameters.k;

	for(int i = 0; i < size_summits; i++)
		superquadric.summits[i] = reverse_bend(superquadric.summits[i], k);
 	
 	return 0;
}