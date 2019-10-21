#include <cloud.h>
#include <jacobi_eigenvalue.h>

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

float** generate_cloud_point(unsigned int uiStacks, unsigned int uiSlices, double fA, double fB, 
							double fC, double e1, double e2, int* size, int xo, int yo, int zo){
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
	
	float** cloud = malloc(sizeof(float*) * (size_tmp + 1));
  
	for(int i = 0; i <= size_tmp; i++)
		cloud[i] = malloc(sizeof(float) * COLUMNS);

	*size = size_tmp;
	size_tmp = 0;
	for(double t = -PI; t <= (PI)+.0001; t += tStep)
	{
		for(double s = -PI; s <= PI+.0001; s += sStep)
		{
			cloud[size_tmp][0] = fA * fexp(cos(t), e1) * fexp(cos(s), e2) + xo;
			cloud[size_tmp][1] = fB * fexp(cos(t), e1) * fexp(sin(s), e2) + yo;
			cloud[size_tmp][2] = fC * fexp(sin(t), e1) + zo;

			size_tmp++;

			cloud[size_tmp][0] = fA * fexp(cos(t+tStep), e1) * fexp(cos(s), e2) + xo;
			cloud[size_tmp][1] = fB * fexp(cos(t+tStep), e1) * fexp(sin(s), e2) + yo;
			cloud[size_tmp][2] = fC * fexp(sin(t+tStep), e1) + zo;

			size_tmp++;
		}
	}

	return cloud;
}

int center_of_gravity(float** cloud, int size, float* tx, float* ty, float* tz){
 	*tx = *ty = *tz = 0;
 	if(cloud == NULL){
 		fprintf(stderr, "center_of_gravity: invalid argument!\n");
		return -1;		
 	}

 	for(int i = 0; i <= size; i++){
 		(*tx) = (*tx) + cloud[i][0];
 		(*ty) = (*ty) + cloud[i][1];
 		(*tz) = (*tz) + cloud[i][2];
 	}

  	(*tx) = (*tx) / (float)size;
 	(*ty) = (*ty) / (float)size;
 	(*tz) = (*tz) / (float)size;

 	(*tx) = floor(*tx + 0.5);
 	(*ty) = floor(*ty + 0.5);
 	(*tz) = floor(*tz + 0.5);

 	return 0;
}

int calculate_matrix_of_rotation(float M[3][3], float R[3][3], float* lambda1, float* lambda2, float* lambda3){
 	float EV[3];
 	float M_[9], R_[9];
 	int it_max = 500;
 	int IT_NUM, ROT_NUM;

 	if(M == NULL || R == NULL){
  		fprintf(stderr, "calculate_matrix_of_rotation: invalid argument!\n");
		return -1;		
 	}

 	*lambda1 = *lambda2 = *lambda3 = 0;
 	for(int i = 0; i < 3; i ++)
 		for(int j = 0; j < 3; j++)
 			R[i][j] = 0;

 	int k = 0;
 	 for(int i = 0; i < 3; i ++){
 		for(int j = 0; j < 3; j++){
 			M_[k] = M[i][j];
 			k++;
 		}
 	}

 	jacobi_eigenvalue(3, M_, it_max, R_, EV, &IT_NUM, &ROT_NUM);

 	for(int i = 0; i < 3; i ++)
 		for(int j = 0; j < 3; j++)
 			R[i][j] = R_[3*i+j];

 	*lambda1 = EV[0];
 	*lambda2 = EV[1];
 	*lambda3 = EV[2];

 	return 0;
}

int calculate_matrix_of_initial_moments(float** cloud, int size, float tx, float ty, float tz, float matrix[3][3]){
 	float x_, y_, z_;
 	if(cloud == NULL || matrix == NULL){
  		fprintf(stderr, "calculate_matrix_of_initial_moments: invalid argument!\n");
		return -1;		
 	}

 	for(int i = 0; i < 3; i ++)
 		for(int j = 0; j < 3; j++)
 			matrix[i][j] = 0;

 	for(int i = 0; i <= size; i++){
 		x_ = cloud[i][0] - tx;
 		y_ = cloud[i][1] - ty;
 		z_ = cloud[i][2] - tz;
 		
 		matrix[0][0] += pow(y_, 2) + pow(z_, 2);
 		matrix[0][1] += -y_ * x_;
 		matrix[0][2] += -z_ * x_;

 		matrix[1][0] += -x_ * y_;
 		matrix[1][1] += pow(x_, 2) + pow(z_, 2);
 		matrix[1][2] += -z_ * y_;

 		matrix[2][0] += -x_ * z_;
 		matrix[2][1] += -y_ * z_;
 		matrix[2][2] += pow(x_, 2) + pow(y_, 2);
 	}

 	for(int i = 0; i < 3; i ++)
 		for(int j = 0; j < 3; j++)
 			matrix[i][j] /= (float)size;

 	return 0;
}

float* get_size_parameters(float** cloud, int size, float tx, float ty, float tz){
	 float* init_size = malloc(sizeof(float) * 3);
	 float max_x, max_y, max_z = -1000000000.0f;
	 float *x, *y, *z;

	 for(int i = 0; i <= size; i++){
	 	if(cloud[i][0] > max_x){
	 		max_x = cloud[i][0];
	 		x = cloud[i];
	 	}
	 	if(cloud[i][1] > max_y){
	 		max_y = cloud[i][1];
	 		y = cloud[i];
	 	}
	 	if(cloud[i][2] > max_z){
	 		max_z = cloud[i][2];
	 		z = cloud[i];
	 	}
	 }

	 init_size[0] = sqrt(pow((-x[0] + tx), 2) + pow((-x[1] + ty), 2) + pow((-x[2] + tz), 2));
	 init_size[1] = sqrt(pow((-y[0] + tx), 2) + pow((-y[1] + ty), 2) + pow((-y[2] + tz), 2));
	 init_size[2] = sqrt(pow((-z[0] + tx), 2) + pow((-z[1] + ty), 2) + pow((-z[2] + tz), 2));

	 return init_size;
}

float* get_rotate_angle(float R[3][3]){
	float* rotate_angle = malloc(sizeof(float) * 3);

 	if(rotate_angle == NULL){
  		fprintf(stderr, "get_rotate_angle: invalid argument!\n");
		return NULL;		
 	}

 	if(R[2][0] != -1.0f && R[2][0] != 1.0f){
 		rotate_angle[1] = -asin(R[2][0]);
 		rotate_angle[0] = atan2(R[2][1] / cos(rotate_angle[1]), R[2][2] / cos(rotate_angle[1]));
 		rotate_angle[2] = atan2(R[1][0] / cos(rotate_angle[1]), R[0][0] / cos(rotate_angle[1]));
 	}
 	else{
 		rotate_angle[2] = 0;
 		if(R[2][0] == -1.0f){
 			rotate_angle[1] = PI / 2;
 			rotate_angle[0] = rotate_angle[2] + atan2(R[0][1], R[0][2]);
 		}
 		else{
 			rotate_angle[1] = -PI / 2;
 			rotate_angle[0] = -rotate_angle[2] + atan2(-R[0][1], -R[0][2]);
 		}
 	}

 	return rotate_angle;
}

float* initial_parameters(float** cloud, int size){
 	float* init_param = malloc(sizeof(float) * 11);
 	float M[3][3];
 	float R[3][3];
 	float lambda1, lambda2, lambda3;


 	if(cloud == NULL || init_param == NULL){
  		fprintf(stderr, "initial_parameters: invalid argument!\n");
		return NULL;		
 	}

 	init_param[0] = 1;
 	init_param[1] = 1;

 	if(center_of_gravity(cloud, size, (init_param + 2), (init_param + 3), (init_param + 4)) < 0){
  		fprintf(stderr, "initial_parameters: invalid argument!\n");
		return NULL;	
 	}

  	if(calculate_matrix_of_initial_moments(cloud, size, init_param[2], init_param[3], init_param[4], M) < 0){
  		fprintf(stderr, "initial_parameters: invalid argument!\n");
		return NULL;	
 	}

   	if(calculate_matrix_of_rotation(M, R, &lambda1, &lambda2, &lambda3)){
  		fprintf(stderr, "initial_parameters: invalid argument!\n");
		return NULL;	
 	}

 	float* init_rotate_angle = get_rotate_angle(R);

 	init_param[5] = init_rotate_angle[0];
 	init_param[6] = init_rotate_angle[1];
 	init_param[7] = init_rotate_angle[2];

 	float* init_size = get_size_parameters(cloud, size, init_param[2], init_param[3], init_param[4]);

 	if(init_size == NULL){
  		fprintf(stderr, "initial_parameters: invalid argument!\n");
		return NULL;	 		
 	}

 	init_param[8] = init_size[0];
 	init_param[9] = init_size[1];
 	init_param[10] = init_size[2];

 	free(init_size);
 	free(init_rotate_angle);

 	return init_param;
 }