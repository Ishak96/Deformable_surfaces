#ifndef DRAW_H
#define DRAW_H

#include <superquadrics.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define R 1.0
#define G 1.0
#define B 1.0

void draw_superquadrics(summit** sum, int m, int n);
void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC, float e1, float e2);

#endif
