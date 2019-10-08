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
	
	float** cloud = malloc(sizeof(float*) * (size_tmp + 1));
  
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

int center_of_gravity(float** cloud, int size, float* tx, float* ty, float* tz){
 	*tx = *ty = *tz = 0;
 	if(cloud == NULL){
 		fprintf(stderr, "center_of_gravity: invalid argument!\n");
		return -1;		
 	}

 	for(int i = 0; i <= size; i++){
 		(*tx) += cloud[i][0];
 		(*ty) += cloud[i][1];
 		(*ty) += cloud[i][2];
 	}

  	(*tx) /= (float)size;
 	(*ty) /= (float)size;
 	(*ty) /= (float)size;	

 	return 0;
}

void igenvalues(float M[3][3], float R[3][3], float* lambda1, float* lambda2, float* lambda3){
	int i, j, p, q, flag;
	float d[3][3], s[3][3], s1[3][3], s1t[3][3];
	float temp[3][3], theta, zero=1e-4, max;

	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			d[i][j] = M[i][j];
			s[i][j] = 0;
		}
	}
	
	for(i = 0; i < 3; i++)
		s[i][i]=1;

	do{
		flag = 0;
		i=1;
		j=2; 
		max = fabs(d[1][2]);

		for(p = 0; p < 3; p++){
			for(q = 0; q < 3; q++){
				if(p!=q){
					if(max < fabs(d[p][q])){
						max = fabs(d[p][q]); 
						i=p; 
						j=q;				
					}				
				}
			}
		}
		
		if(d[i][i] == d[j][j]){
			if(d[i][j] > 0)
				theta = PI / 4;
			else
				theta = -PI / 4;
		}
		else{
			theta = 0.5 * atan(2 * d[i][j] / (d[i][i] - d[j][j]));
		}
		
		for(p = 0; p < 3; p++){
			for(q = 0; q < 3; q++){
				s1[p][q]=0;
				s1t[p][q]=0;
			}
		}
		
		for(p = 0; p < 3; p++){
			s1[p][p] = 1; 
			s1t[p][p] = 1;
		}
		
		s1[i][i] = cos(theta); 
		s1[j][j] = s1[i][i];
		s1[j][i] = sin(theta); 
		s1[i][j] = -s1[j][i];
		s1t[i][i] = s1[i][i]; 
		s1t[j][j] = s1[j][j];
		s1t[i][j] = s1[j][i]; 
		s1t[j][i] = s1[i][j];

		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				temp[i][j] = 0;

				for(p = 0;p < 3; p++){
					temp[i][j] += s1t[i][p] * d[p][j];
				}
			}
		}

		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				d[i][j] = 0;

				for(p = 0; p < 3; p++){
					d[i][j] += temp[i][p] * s1[p][j];
				}
			}
		}

		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				temp[i][j] = 0;
				
				for(p = 0;p < 3; p++){
					temp[i][j] += s[i][p] * s1[p][j];
				}
			}			
		}

		for(i = 0; i < 3; i++)
			for(j = 0; j < 3; j++) 
				s[i][j] = temp[i][j];

		for(i = 0; i < 3; i++){
			for(j = 0; j < 3;j++){
				if(i != j)
					if(fabs(d[i][j] > zero)) 
						flag = 1;
			}
		}

	}while(flag == 1);

	*lambda1 = d[0][0];
	*lambda2 = d[1][1];
	*lambda3 = d[2][2];


	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			R[j][i] = s[i][j];
}

int calculate_matrix_of_rotation(float M[3][3], float R[3][3], float* lambda1, float* lambda2, float* lambda3){
 	if(M == NULL || R == NULL){
  		fprintf(stderr, "calculate_matrix_of_rotation: invalid argument!\n");
		return -1;		
 	}

 	*lambda1 = *lambda2 = *lambda3 = 0;
 	for(int i = 0; i < 3; i ++)
 		for(int j = 0; j < 3; j++)
 			R[i][j] = 0;

 	igenvalues(M, R, lambda1, lambda2, lambda3);

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

	 for(int i = 0; i <= size; i++){
	 	if(cloud[i][0] > max_x)
	 		max_x = cloud[i][0];
	 	if(cloud[i][1] > max_y)
	 		max_y = cloud[i][1];
	 	if(cloud[i][2] > max_z)
	 		max_z = cloud[i][2];
	 }

	 init_size[0] = (tx > max_x) ? (tx - max_x) : (max_x - tx);
	 init_size[1] = (ty > max_y) ? (ty - max_y) : (max_y - ty);
	 init_size[2] = (tz > max_z) ? (tz - max_z) : (max_z - tz);

	 return init_size;
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

 	init_param[5] = -asin(R[0][2]);
 	init_param[6] = atan2(-R[1][2] / cos(init_param[5]), -R[2][2] / cos(init_param[5]));
 	init_param[7] = atan2(-R[0][1] / cos(init_param[6]), -R[0][0] / cos(init_param[6]));

 	float* init_size = get_size_parameters(cloud, size, init_param[2], init_param[3], init_param[4]);

 	init_param[8] = init_size[0];
 	init_param[9] = init_size[1];
 	init_param[10] = init_size[2];

 	free(init_size);

 	return init_param;
 }