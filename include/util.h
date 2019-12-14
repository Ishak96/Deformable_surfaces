#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <superquadrics.h>

int** allocIntMatrix(int rows, int cols);
void freeIntMatrix(int** MAT, int rows);
SUMMIT* allocSUMMITTable(int n);
void freeSUMMITTable(SUMMIT* summits);
float* allocFloatTable(int n);
void freeFloatTable(float* table);
float* discretization(float a, float b, int amount);
void default_PHIvect_THETAvect(float phi[], float theta[]);

#endif
