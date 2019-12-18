#include <stdio.h>
#include <stdlib.h>
#include <superquadrics.h>
#include <util.h>

int main(int argc, char const *argv[]){
	
	if(argc < 8){
		fprintf(stderr, "main: invalid argument!\n");
		printf("usage: %s [a] [b] [c] [e1] [e2] [r0] [r1]..\n", argv[0]);
		printf("give r0 = 0 and r1 = 1 to gener a normal superquadrics\n");
		return -1;
	}

	int parallels = 150;
	int meridians = 150;

	PARAMETERS parameters;

	parameters.a1 = atof(argv[1]);
	parameters.a2 = atof(argv[2]);
	parameters.a3 = atof(argv[3]);
	parameters.e1 = atof(argv[4]);
	parameters.e2 = atof(argv[5]);
	parameters.r0 = atof(argv[6]);
	parameters.r1 = atof(argv[7]);

	SUPERQUADRIC superquadric;

	superquadric.parameters = parameters;
	superquadric.parallels = parallels;
	superquadric.meridians = meridians;
	superquadric.size_summits = (parallels - 2) * (meridians - 1) + 2;

	float phi[2];
	float theta[2];
	default_PHIvect_THETAvect(phi, theta);

	summit_building(&superquadric, phi, theta);

	for(int i = 0; i < superquadric.size_summits; i++){
		printf("SUMMIT[%d] --> {%f,%f,%f}\n", i
											, superquadric.summits[i].x
											, superquadric.summits[i].y
											, superquadric.summits[i].z);
	}

	return 0;
}