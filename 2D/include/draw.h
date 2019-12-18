#ifndef DRAW_H
#define DRAW_H

#include <superquadrics.h>
#include <deformation.h>
#include <cloud.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <stdio.h>

#define R_C 1
#define G_C 1
#define B_C 1
#define POINTS_SIZE 1

void draw_SUPERQUADRIC(SUPERQUADRIC superquadric);

void draw_debug(SUPERQUADRIC superquadric);

void draw_cloud(CLOUD cloud, float R, float G, float B);

int getRootWindowSize(int *w, int *h);

int getScreenSize(int *w, int*h);

#endif
