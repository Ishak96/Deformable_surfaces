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
	float delta3 = sum1.z - sum2.z;
	return 	   (delta1 >= -DELTA && delta1 <= DELTA)
			&& (delta2 >= -DELTA && delta2 <= DELTA) 
			&& (delta3 >= -DELTA && delta3 <= DELTA);
}

SUMMIT func_eval(float a, float b, float c, float e1, float e2,
				 float phi, float theta){
	SUMMIT summit;

	summit.x = a * (fexp(cos(phi), e1)) * (fexp(cos(theta), e2));
	summit.y = b * (fexp(cos(phi), e1)) * (fexp(sin(theta), e2));
	summit.z = c * (fexp(sin(phi), e1));

	return summit;
}

SUMMIT create_SUMMIT(PARAMETERS parameters, float phi, float theta){
	float a = parameters.a1;
	float b = parameters.a2;
	float c = parameters.a3;
	float e1 = parameters.e1;
	float e2 = parameters.e2;

	return func_eval(a, b, c, e1, e2, phi, theta);
}

void summit_building(SUPERQUADRIC* superquadric, float phi[], float theta[]){
	int lengthSummit = superquadric->size_summits;
	int parallels = superquadric->parallels; 
	int meridians = superquadric->meridians;

	PARAMETERS parameters = superquadric->parameters;

	SUMMIT* summits = allocSUMMITTable(lengthSummit);

	float* Uvect = discretization(phi[0], phi[1], parallels);
	float* Vvect = discretization(theta[0], theta[1], meridians);

	int nSummits = 0;

	/*South summit*/
	float u = Uvect[0];
	float v = Vvect[0];
	summits[nSummits] = create_SUMMIT(parameters, u, v);
	nSummits++;
	
	for(int p = 1; p <= (parallels-2); p++){
		u = Uvect[p];
		for(int m = 0; m <= (meridians-2); m++){
			/*Intermediate summit*/
			v = Vvect[m];
			summits[nSummits] = create_SUMMIT(parameters, u, v);
			nSummits++;
		}
	}

	/*North summit*/
	u = Uvect[parallels-1];
	v = Vvect[0];
	summits[nSummits] = create_SUMMIT(parameters, u, v);
	nSummits++;


	superquadric->summits = summits;
	freeFloatTable(Uvect);
	freeFloatTable(Vvect);
}

void facade_building(SUPERQUADRIC* superquadric){
	int lengthFacade = superquadric->size_facades;
	int parallels = superquadric->parallels; 
	int meridians = superquadric->meridians;

	int** facades = allocIntMatrix(lengthFacade, NB_COLS_FACADES);

	int nFacades = 0;

	/*Create south facades*/
	for(int m = 1; m <= (meridians-2); m++){
		facades[nFacades][0] = 3;
		facades[nFacades][1] = 0;
		facades[nFacades][2] = m+1;
		facades[nFacades][3] = m;
		nFacades++;
	}
	
	facades[nFacades][0] = 3;
	facades[nFacades][1] = 0;
	facades[nFacades][2] = 1;
	facades[nFacades][3] = meridians-1;
	nFacades++;

	/*Create intermediate facade*/
	for(int p = 1; p <= (parallels-3); p++){
		for(int m = 1; m <= (meridians-2); m++){
			facades[nFacades][0] = 4;
			facades[nFacades][1] = (p-1)*(meridians-1)+m;
			facades[nFacades][2] = (p-1)*(meridians-1)+m+1;
			facades[nFacades][3] = p*(meridians-1)+m+1;
			facades[nFacades][4] = p*(meridians-1)+m;
			nFacades++;		
		}

		facades[nFacades][0] = 4;
		facades[nFacades][1] = p*(meridians-1);
		facades[nFacades][2] = (p-1)*(meridians-1)+1;
		facades[nFacades][3] = p*(meridians-1)+1;
		facades[nFacades][4] = (p+1)*(meridians-1);
		nFacades++;
	}

	/*Create north facades*/
	for(int m = 1; m <= (meridians-2); m++){
		facades[nFacades][0] = 3;
		facades[nFacades][1] = (parallels-3)*(meridians-1)+m;
		facades[nFacades][2] = (parallels-3)*(meridians-1)+m+1;
		facades[nFacades][3] = (parallels-2)*(meridians-1)+1;
		nFacades++;
	}
	
	facades[nFacades][0] = 3;
	facades[nFacades][1] = (parallels-3)*(meridians-1)+(meridians-1);
	facades[nFacades][2] = (parallels-3)*(meridians-1)+1;
	facades[nFacades][3] = (parallels-2)*(meridians-1)+1;
	nFacades++;

	superquadric->facades = facades;
}

SUPERQUADRIC create_superquadrics(float a, float b, float c, float e1, float e2, 
								  int parallels, int meridians,
								  float phi[], float theta[]){
	SUPERQUADRIC superquadric;
	PARAMETERS parameters;

	parameters.a1 = a;
	parameters.a2 = b;
	parameters.a3 = c;
	parameters.e1 = e1;
	parameters.e2 = e2;
	
	superquadric.parallels = parallels;
	superquadric.meridians = meridians;
	superquadric.parameters = parameters;
	superquadric.size_summits = (parallels - 2) * (meridians - 1) + 2;
	superquadric.size_facades = (parallels - 1) * (meridians - 1);

	facade_building(&superquadric);
	summit_building(&superquadric, phi, theta);

	return superquadric;
}

void destroy_superquadrics(SUPERQUADRIC* superquadric){
	if(superquadric->summits)
		freeSUMMITTable(superquadric->summits);
	if(superquadric->facades)
		freeIntMatrix(superquadric->facades, superquadric->size_facades);
}