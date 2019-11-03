#ifndef DEFORMATION_H
#define DEFORMATION_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int taper(float** cloud, int size, float kx, float ky);
int reverse_taper(float** cloud, int size, float kx, float ky);
int bend(float** cloud, int size, float k, float alpha);
int reverse_bend(float** cloud, int size, float k, float alpha);

#endif