#include <util.h>

int** allocIntMatrix(int rows, int cols){
	
	int** MAT = (int **)malloc(rows * sizeof(int *));

	for(int i = 0; i < rows; i++)
		MAT[i] = (int *)malloc(cols * sizeof(int));

	return MAT;
}

float** allocFloatMatrix(int rows, int cols){
	
	float** MAT = (float **)malloc(rows * sizeof(float *));

	for(int i = 0; i < rows; i++)
		MAT[i] = (float *)malloc(cols * sizeof(float));

	return MAT;
}

void freeIntMatrix(int** MAT, int rows){
	if(MAT){
		for(int i = 0; i < rows; i++)
			free(MAT[i]);
		free(MAT);
	}
}

void freeFloatMatrix(float** MAT, int rows){
	if(MAT){
		for(int i = 0; i < rows; i++)
			free(MAT[i]);
		free(MAT);
	}
}

SUMMIT* allocSUMMITTable(int n){
	
	SUMMIT* summits = (SUMMIT* )malloc(n * sizeof(SUMMIT));

	return summits;
}

void freeSUMMITTable(SUMMIT* summits){
	if(summits)
		free(summits);
}

float* allocFloatTable(int n){
	float* table = (float *)malloc(n * sizeof(float));

	return table;
}

void freeFloatTable(float* table){
	if(table)
		free(table);
}

float* discretization(float a, float b, int amount){
	float* discreetVector = allocFloatTable(amount);

	float step = (b-a) / (float)(amount-1);
	discreetVector[0] = a;
	for(int i = 1; i < amount; i++){
		discreetVector[i] = discreetVector[i-1]+step;
	}

	return discreetVector;
}

void default_PHIvect_THETAvect(float phi[], float theta[]){
	phi[0] = -PHI;
	phi[1] = PHI;

	theta[0] = -THETA;
	theta[1] = THETA;
}