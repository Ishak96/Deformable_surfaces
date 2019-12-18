#include <stdio.h>
#include <stdlib.h>
#include <util.h>

int main(int argc, char const *argv[]){
	
	if(argc < 3){
		printf("Invalid usage of the test, invalid parameters\n");
		fprintf(stderr, "usage : %s [a] [b] [amount]\n", argv[0]);
		return -1;
	}

	float a = atof(argv[1]);
	float b = atof(argv[2]);
	if(a > b){
		printf("Invalid usage of the test, invalid parameters\n");
		fprintf(stderr, "usage : %s [a]<[b] [amount]\n", argv[0]);
		return -1;		
	}

	int amount = atoi(argv[3]);

	float* discreetVector = discretization(a, b, amount);

	printf("for {%f,%f} and amount = [%d]\n", a, b, amount);
	printf("--------------------------------------\n\n");

	for(int i = 0; i < amount; i++){
		printf("%f ", discreetVector[i]);
	}
	printf("\n");

	freeFloatTable(discreetVector);

	return 0;
}