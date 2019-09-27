#ifndef DRAW_H
#define DRAW_H

#include <superquadrics.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define R 0.60
#define G 0.75
#define B 1.0

void draw_superquadrics(summit** sum, double m, double n);
void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, double fA, double fB, double fC, double e1, double e2);

#endif
