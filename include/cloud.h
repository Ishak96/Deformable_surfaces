#ifndef CLOUD_H
#define CLOUD_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <jacobi_eigenvalue.h>
#include <util.h>
#include <superquadrics.h>

#define COLUMNS 3

typedef struct{
	int size;
	float** points;
}CLOUD;

int get_size_cloud(const char* file_name);

CLOUD get_cloud_point(const char* file_name, float fact);

CLOUD generate_cloud_point(float a, float b, float c, float e1, float e2);

void center_of_gravity(CLOUD cloud, PARAMETERS* parameters);

void calculate_matrix_of_rotation(float M[3][3], float R[3][3], float* lambda1, float* lambda2, float* lambda3);

void calculate_matrix_of_initial_moments(CLOUD cloud, PARAMETERS parameters, float matrix[3][3]);

void get_size_parameters(CLOUD cloud, PARAMETERS* parameters);

void get_rotate_angle(float R[3][3], PARAMETERS* parameters);

PARAMETERS initial_parameters(CLOUD cloud);

#endif
