#include <stdio.h>
#include <stdlib.h>
#include <superquadrics.h>

int main(int argc, char const *argv[]){
	
	if(argc < 2){
		printf("Invalid usage of the test, invalid parameters\n");
		fprintf(stderr, "usage : %s [parallels] [meridians]\n", argv[0]);
		return -1;
	}

	int parallels = atoi(argv[1]);
	int meridians = atoi(argv[2]);
	SUPERQUADRIC superquadric;

	superquadric.size_facades = (parallels - 1) * (meridians - 1);
	superquadric.parallels = parallels;
	superquadric.meridians = meridians;

	facade_building(&superquadric);

	printf("for parallels = [%d], meridians = [%d] \n", parallels, meridians);
	printf("--------------------------------------\n\n");

	for(int i = 0; i < superquadric.size_facades; i++){
		int summit_size = superquadric.facades[i][0];
		printf("----%s----\n", (summit_size == 3) ? "triangle" : "rectangle");
		for(int j = 1; j <= summit_size; j++)
			printf("%d ", superquadric.facades[i][j]);
		printf("\n");
	}

	return 0;
}