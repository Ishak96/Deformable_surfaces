#include <cloud.h>

int get_size_cloud(const char* file_name){
	FILE* file;

	if( file_name == NULL ){
		fprintf(stderr, "get_size_cloud: invalid argument!\n");
		return -1;
	}

	file=fopen(file_name, "r+");

	if( file == NULL ){
		fprintf(stderr, "get_size_cloud: can't open file !\n");
		return -1;
	}

	char c;
	int size = 0;
	for(c = getc(file); c != EOF; c = getc(file)) 
		if (c == '\n')
			size = size + 1; 

	size++;
	fclose(file);
	return size;	
}

float** get_cloud_point(const char* file_name, int* size, float fact){
	FILE* file;
	float x, y, z;

	if( file_name == NULL ){
		fprintf(stderr, "get_cloud_point: invalid argument!\n");
		return NULL;
	}

	file=fopen(file_name, "r+");

	if( file == NULL ){
		fprintf(stderr, "get_cloud_point: can't open file !\n");
		return NULL;
	}

	*size = get_size_cloud(file_name);
	if( size < 0 ){
		fprintf(stderr, "get_cloud_point: can't open file !\n");
		return NULL;
	}

	float** cloud = malloc(sizeof(float*) * (*size));
  
	for(int i = 0; i <= *size; i++)
		cloud[i] = malloc(sizeof(float) * COLUMNS);

	int i = 0;
	while(i <= *size){
		fscanf(file, "%f %f %f\n", &x, &y, &z);
		
		cloud[i][0] = x * fact;
		cloud[i][1] = y * fact;
		cloud[i][2] = z * fact;

		i++;
	}

	return cloud;
}

float** generate_cloud_point(unsigned int uiStacks, unsigned int uiSlices, double fA, double fB, double fC, double e1, double e2, int* size){
	double tStep = (PI) / (double)uiSlices;
	double sStep = (PI) / (double)uiStacks;
	
	int size_tmp = 0;

	for(double t = -PI; t <= (PI)+.0001; t += tStep)
	{
		for(double s = -PI; s <= PI+.0001; s += sStep)
		{
			size_tmp+=2;
		}
	}
	
	float** cloud = malloc(sizeof(float*) * (size_tmp));
  
	for(int i = 0; i <= size_tmp; i++)
		cloud[i] = malloc(sizeof(float) * COLUMNS);

	*size = size_tmp;
	size_tmp = 0;
	for(double t = -PI; t <= (PI)+.0001; t += tStep)
	{
		for(double s = -PI; s <= PI+.0001; s += sStep)
		{
			cloud[size_tmp][0] = fA * fexp(cos(t), e1) * fexp(cos(s), e2);
			cloud[size_tmp][1] = fB * fexp(cos(t), e1) * fexp(sin(s), e2);
			cloud[size_tmp][2] = fC * fexp(sin(t), e1);

			size_tmp++;

			cloud[size_tmp][0] = fA * fexp(cos(t+tStep), e1) * fexp(cos(s), e2);
			cloud[size_tmp][1] = fB * fexp(cos(t+tStep), e1) * fexp(sin(s), e2);
			cloud[size_tmp][2] = fC * fexp(sin(t+tStep), e1);

			size_tmp++;
		}
	}

	return cloud;
}