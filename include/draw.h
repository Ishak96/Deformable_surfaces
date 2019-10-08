#ifndef DRAW_H
#define DRAW_H

#include <superquadrics.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <stdio.h>

#define r 0.60
#define g 0.75
#define b 1.0
#define POINTS_SIZE 1

void draw_superquadrics(summit** sum, double m, double n);
void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, double fA, double fB, double fC, double e1, double e2);
void DrawEllipsoid_cloud(unsigned int uiStacks, unsigned int uiSlices, double fA, double fB, double fC, double e1, double e2);
void draw_cloud_point(float** cloud, int size, float* color);
int getRootWindowSize(int *w, int *h);
int getScreenSize(int *w, int*h);

#endif
