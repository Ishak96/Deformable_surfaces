#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#include <util.h>
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

int equals_summit(SUMMIT sum1, SUMMIT sum2){
	float delta1 = sum1.x - sum2.x;
	float delta2 = sum1.y - sum2.y;
	return 	   (delta1 >= -DELTA && delta1 <= DELTA)
			&& (delta2 >= -DELTA && delta2 <= DELTA);
}

SUMMIT func_eval(float a, float b, float e, float phi){
	SUMMIT summit;

	summit.x = a * (fexp(cos(phi), e));
	summit.y = b * (fexp(sin(phi), e));

	return summit;
}

SUMMIT create_SUMMIT(PARAMETERS parameters, float phi){
	float a = parameters.a1;
	float b = parameters.a2;
	float e = parameters.e;

	return func_eval(a, b, e, phi);
}

float SUMMIT_distance(SUMMIT sum1, SUMMIT sum2){
	float pow_x = pow((sum2.x - sum1.x), 2);
	float pow_y = pow((sum2.y - sum1.y), 2);

	return sqrt(pow_x + pow_y);
}

void summit_building(SUPERQUADRIC* superquadric, float phi[]){
	int lengthSummit = superquadric->size_summits;

	PARAMETERS parameters = superquadric->parameters;

	SUMMIT* summits = allocSUMMITTable(lengthSummit);

	float* Uvect = discretization(phi[0], phi[1], lengthSummit);

	int nSummits = 0;

	/*South summit*/
	float u = Uvect[0];
	summits[nSummits] = create_SUMMIT(parameters, u);
	nSummits++;
	
	for(int p = 1; p <= (lengthSummit-2); p++){
		u = Uvect[p];
		summits[nSummits] = create_SUMMIT(parameters, u);
		nSummits++;
	}

	/*North summit*/
	u = Uvect[lengthSummit-1];
	summits[nSummits] = create_SUMMIT(parameters, u);
	nSummits++;

	superquadric->summits = summits;
	freeFloatTable(Uvect);
}

SUPERQUADRIC create_superquadrics(float a, float b, float e, int length, float phi[]){
	SUPERQUADRIC superquadric;
	PARAMETERS parameters;

	parameters.a1 = a;
	parameters.a2 = b;
	parameters.e = e;
	
	superquadric.size_summits = length;
	superquadric.parameters = parameters;

	summit_building(&superquadric, phi);

	return superquadric;
}

void destroy_superquadrics(SUPERQUADRIC* superquadric){
	if(superquadric->summits)
		freeSUMMITTable(superquadric->summits);
}