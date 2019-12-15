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
	float x, y, z;
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
	while(i <= cloud.size){
		fscanf(file, "%f %f %f\n", &x, &y, &z);
		
		points[i][0] = x * fact;
		points[i][1] = y * fact;
		points[i][2] = z * fact;

		i++;
	}
	cloud.points = points;

	fclose(file);
	return cloud;
}

CLOUD generate_cloud_point(float a, float b, float c, float e1, float e2){

	CLOUD cloud;
	SUPERQUADRIC superquadric;
	PARAMETERS parameters;

	parameters.a1 = a;
	parameters.a2 = b;
	parameters.a3 = c;
	parameters.e1 = e1;
	parameters.e2 = e2;

	int parallels = 30;
	int meridians = 30;
	
	superquadric.parallels = parallels;
	superquadric.meridians = meridians;
	superquadric.parameters = parameters;
	superquadric.size_summits = (parallels - 2) * (meridians - 1) + 2;

	float phi[2]; float theta[2];
	default_PHIvect_THETAvect(phi, theta);

	summit_building(&superquadric, phi, theta);

	cloud.size = superquadric.size_summits;
	float** points = allocFloatMatrix(cloud.size, COLUMNS);

	SUMMIT* sum = superquadric.summits;
	for(int i = 0; i < superquadric.size_summits; i++){
		points[i][0] = sum[i].x;
		points[i][1] = sum[i].y;
		points[i][2] = sum[i].z;
	}
	cloud.points = points;

	freeSUMMITTable(superquadric.summits);
	return cloud;
}

void center_of_gravity(CLOUD cloud, PARAMETERS* parameters){
 	float tx, ty, tz;

 	tx = ty = tz = 0;

 	for(int i = 0; i < cloud.size; i++){
 		tx = tx + cloud.points[i][0];
 		ty = ty + cloud.points[i][1];
 		tz = tz + cloud.points[i][2];
 	}

  	tx = tx / (float)cloud.size;
 	ty = ty / (float)cloud.size;
 	tz = tz / (float)cloud.size;

 	tx = floor(tx + 0.5);
 	ty = floor(ty + 0.5);
 	tz = floor(tz + 0.5);

 	parameters->tx = tx;
 	parameters->ty = ty;
 	parameters->tz = tz;
}

void calculate_matrix_of_rotation(float M[3][3], float R[3][3], float* lambda1, float* lambda2, float* lambda3){
 	float EV[3];
 	float M_[9], R_[9];
 	int it_max = 500;
 	int IT_NUM, ROT_NUM;

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
}

void calculate_matrix_of_initial_moments(CLOUD cloud, PARAMETERS parameters, float matrix[3][3]){
 	float x, y, z;

 	for(int i = 0; i < 3; i ++)
 		for(int j = 0; j < 3; j++)
 			matrix[i][j] = 0;

 	for(int i = 0; i < cloud.size; i++){
 		x = cloud.points[i][0] - parameters.tx;
 		y = cloud.points[i][1] - parameters.ty;
 		z = cloud.points[i][2] - parameters.tz;
 		
 		matrix[0][0] += pow(y, 2) + pow(z, 2);
 		matrix[0][1] += -y * x;
 		matrix[0][2] += -z * x;

 		matrix[1][0] += -x * y;
 		matrix[1][1] += pow(x, 2) + pow(z, 2);
 		matrix[1][2] += -z * y;

 		matrix[2][0] += -x * z;
 		matrix[2][1] += -y * z;
 		matrix[2][2] += pow(x, 2) + pow(y, 2);
 	}

 	for(int i = 0; i < 3; i ++)
 		for(int j = 0; j < 3; j++)
 			matrix[i][j] /= (float)cloud.size;
}

void get_size_parameters(CLOUD cloud, PARAMETERS* parameters){
	 float max_x, max_y, max_z = -1000000000.0f;

	 for(int i = 0; i < cloud.size; i++){
	 	if(cloud.points[i][0] > max_x){
	 		max_x = cloud.points[i][0];
	 	}
	 	if(cloud.points[i][1] > max_y){
	 		max_y = cloud.points[i][1];
	 	}
	 	if(cloud.points[i][2] > max_z){
	 		max_z = cloud.points[i][2];
	 	}
	 }

	 parameters->a1 = sqrt(pow(max_x, 2) + pow(parameters->tx, 2));
	 parameters->a2 = sqrt(pow(max_y, 2) + pow(parameters->ty, 2));
	 parameters->a3 = sqrt(pow(max_z, 2) + pow(parameters->tz, 2));
}

void get_rotate_angle(float R[3][3], PARAMETERS* parameters){

 	if(R[2][0] != -1.0f && R[2][0] != 1.0f){
 		parameters->angle2 = -asin(R[2][0]);
 		parameters->angle1 = atan2(R[2][1] / cos(parameters->angle2), R[2][2] / cos(parameters->angle2));
 		parameters->angle3 = atan2(R[1][0] / cos(parameters->angle2), R[0][0] / cos(parameters->angle2));
 	}
 	else{
 		parameters->angle3 = 0;
 		if(R[2][0] == -1.0f){
 			parameters->angle2 = PI / 2;
 			parameters->angle1 = parameters->angle3 + atan2(R[0][1], R[0][2]);
 		}
 		else{
 			parameters->angle2 = -PI / 2;
 			parameters->angle1 = -parameters->angle3 + atan2(-R[0][1], -R[0][2]);
 		}
 	}
}

PARAMETERS initial_parameters(CLOUD cloud){
 	float M[3][3];
 	float R[3][3];
 	float lambda1, lambda2, lambda3;

 	PARAMETERS parameters;

 	parameters.e1 = 1;
 	parameters.e2 = 1;

 	center_of_gravity(cloud, &parameters);

 	calculate_matrix_of_initial_moments(cloud, parameters, M);

   	calculate_matrix_of_rotation(M, R, &lambda1, &lambda2, &lambda3);

	get_rotate_angle(R, &parameters);

	get_size_parameters(cloud, &parameters);

 	return parameters;
 }