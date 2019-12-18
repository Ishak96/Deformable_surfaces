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

CLOUD get_cloud_point(const char* file_name, float fact){
	FILE* file;
	float x, y;
	CLOUD cloud;

	if( file_name == NULL ){
		fprintf(stderr, "get_cloud_point: invalid argument!\n");
	}

	file=fopen(file_name, "r+");

	if( file == NULL ){
		fprintf(stderr, "get_cloud_point: can't open file !\n");
	}

	cloud.size = get_size_cloud(file_name);
	if( cloud.size < 0 ){
		fprintf(stderr, "get_cloud_point: can't open file !\n");
	}

	float** points = allocFloatMatrix(cloud.size, COLUMNS);

	int i = 0;
	while(i < cloud.size){
		fscanf(file, "%f %f\n", &x, &y);
		
		points[i][0] = x * fact;
		points[i][1] = y * fact;

		i++;
	}
	cloud.points = points;

	fclose(file);
	return cloud;
}

CLOUD generate_cloud_point(float a, float b, float e){

	CLOUD cloud;
	SUPERQUADRIC superquadric;
	PARAMETERS parameters;

	parameters.a1 = a;
	parameters.a2 = b;
	parameters.e = e;

	int length = 50;
	
	superquadric.size_summits = length;
	superquadric.parameters = parameters;

	float phi[2]; float theta[2];
	default_PHIvect_THETAvect(phi, theta);

	summit_building(&superquadric, theta);

	cloud.size = superquadric.size_summits;
	float** points = allocFloatMatrix(cloud.size, COLUMNS);

	SUMMIT* sum = superquadric.summits;
	for(int i = 0; i < superquadric.size_summits; i++){
		points[i][0] = sum[i].x;
		points[i][1] = sum[i].y;
	}
	cloud.points = points;

	freeSUMMITTable(superquadric.summits);
	return cloud;
}

void center_of_gravity(CLOUD cloud, PARAMETERS* parameters){
 	float tx, ty;

 	tx = ty = 0;

 	for(int i = 0; i < cloud.size; i++){
 		tx = tx + cloud.points[i][0];
 		ty = ty + cloud.points[i][1];
 	}

  	tx = tx / (float)cloud.size;
 	ty = ty / (float)cloud.size;

 	tx = floor(tx + 0.5);
 	ty = floor(ty + 0.5);

 	parameters->tx = tx;
 	parameters->ty = ty;
}

void calculate_matrix_of_rotation(float M[2][2], float R[2][2], float* lambda1, float* lambda2){
 	float EV[2];
 	float M_[4], R_[4];
 	int it_max = 500;
 	int IT_NUM, ROT_NUM;

 	*lambda1 = *lambda2 = 0;
 	for(int i = 0; i < 2; i ++)
 		for(int j = 0; j < 2; j++)
 			R[i][j] = 0;

 	int k = 0;
 	 for(int i = 0; i < 2; i ++){
 		for(int j = 0; j < 2; j++){
 			M_[k] = M[i][j];
 			k++;
 		}
 	}

 	jacobi_eigenvalue(2, M_, it_max, R_, EV, &IT_NUM, &ROT_NUM);

 	for(int i = 0; i < 2; i ++)
 		for(int j = 0; j < 2; j++)
 			R[i][j] = R_[2*i+j];

 	*lambda1 = EV[0];
 	*lambda2 = EV[1];
}

void calculate_matrix_of_initial_moments(CLOUD cloud, PARAMETERS parameters, float matrix[2][2]){
 	float x, y;

 	for(int i = 0; i < 2; i ++)
 		for(int j = 0; j < 2; j++)
 			matrix[i][j] = 0;

 	for(int i = 0; i < cloud.size; i++){
 		x = cloud.points[i][0] - parameters.tx;
 		y = cloud.points[i][1] - parameters.ty;
 		
 		matrix[0][0] += pow(y, 2);
 		matrix[0][1] += -y * x;

 		matrix[1][0] += -x * y;
 		matrix[1][1] += pow(x, 2);
 	}

 	for(int i = 0; i < 2; i ++)
 		for(int j = 0; j < 2; j++)
 			matrix[i][j] /= (float)cloud.size;
}

void get_size_parameters(CLOUD cloud, PARAMETERS* parameters){
	 float max_x = -1000000000.0f;
	 float max_y = -1000000000.0f;
	 SUMMIT sum_x,sum_y,sum_center;

	 sum_center.x = parameters->tx;
	 sum_center.y = parameters->ty;

	 for(int i = 0; i < cloud.size; i++){

	 	if(cloud.points[i][0] > max_x){
	 		max_x = cloud.points[i][0];

	 		sum_x.x = max_x;
	 		sum_x.y = cloud.points[i][1];
	 	}
	 	if(cloud.points[i][1] > max_y){
	 		max_y = cloud.points[i][1];

	 		sum_y.x = cloud.points[i][0];
	 		sum_y.y = max_y;
	 	}
	 }

	 parameters->a1 = SUMMIT_distance(sum_center, sum_x);
	 parameters->a2 = SUMMIT_distance(sum_center, sum_y);
}

void get_rotate_angle(float R[2][2], PARAMETERS* parameters){

 	if(R[1][0] != -1.0f && R[1][0] != 1.0f){
 		parameters->angle = -asin(R[1][0]);
 	}
 	else{
 		if(R[1][0] == -1.0f){
 			parameters->angle = PI / 2;
 		}
 		else{
 			parameters->angle = -PI / 2;
 		}
 	}
}

PARAMETERS initial_parameters(CLOUD cloud){
 	float M[2][2];
 	float R[2][2];
 	float lambda1, lambda2;

 	PARAMETERS parameters;

 	parameters.e = 1;

 	center_of_gravity(cloud, &parameters);

 	calculate_matrix_of_initial_moments(cloud, parameters, M);

   	calculate_matrix_of_rotation(M, R, &lambda1, &lambda2);

	get_rotate_angle(R, &parameters);

	get_size_parameters(cloud, &parameters);

 	return parameters;
 }

 void freeCLOUD(CLOUD* cloud){
 	if(cloud->points){
 		freeFloatMatrix(cloud->points, cloud->size);
 		cloud->size = 0;
 	}
 }