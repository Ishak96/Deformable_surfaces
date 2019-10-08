#ifndef CLOUD_H
#define CLOUD_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <superquadrics.h>

#define COLUMNS 3

int get_size_cloud(const char* file_name);
float** get_cloud_point(const char* file_name, int* size, float fact);
float** generate_cloud_point(unsigned int uiStacks, unsigned int uiSlices, double fA, double fB, double fC, double e1, double e2, int* size);
void igenvalues(float M[3][3], float R[3][3], float* lambda1, float* lambda2, float* lambda3);
int calculate_matrix_of_rotation(float M[3][3], float R[3][3], float* lambda1, float* lambda2, float* lambda3);
int calculate_matrix_of_initial_moments(float** cloud, int size, float tx, float ty, float tz, float matrix[3][3]);
float* get_size_parameters(float** cloud, int size, float tx, float ty, float tz);
float* initial_parameters(float** cloud, int size);

#endif
