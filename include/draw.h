#ifndef DRAW_H
#define DRAW_H

#include <superquadrics.h>
#include <deformation.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <stdio.h>

#define r 1
#define g 1
#define b 1
#define POINTS_SIZE 2

void draw_superquadrics(superquadrics forme);
void draw_debug(superquadrics forme);
void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC, float e1, float e2);
void DrawEllipsoid_cloud(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC, float e1, float e2);
void draw_cloud_point(float** cloud, int size, float* color);
int getRootWindowSize(int *w, int *h);
int getScreenSize(int *w, int*h);

#endif
