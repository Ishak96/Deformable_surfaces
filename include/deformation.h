#ifndef DEFORMATION_H
#define DEFORMATION_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <superquadrics.h>
#include <deformation.h>

SUMMIT taper(SUMMIT sum, float kx, float ky, float a3);
SUMMIT bend(SUMMIT sum, float k, float alpha);
SUMMIT twist(SUMMIT sum, float nt, float a1);
int taper_SUPERQUADRIC(SUPERQUADRIC superquadric);
int bend_SUPERQUADRIC(SUPERQUADRIC superquadric);
int twist_SUPERQUADRIC(SUPERQUADRIC superquadric);

SUMMIT reverse_taper(SUMMIT sum, float kx, float ky, float a3);
SUMMIT reverse_bend(SUMMIT sum, float k, float alpha);
SUMMIT reverse_twist(SUMMIT sum, float nt, float a1);
int reverse_taper_SUPERQUADRIC(SUPERQUADRIC superquadric);
int reverse_bend_SUPERQUADRIC(SUPERQUADRIC superquadric);
int reverse_twist_SUPERQUADRIC(SUPERQUADRIC superquadric);

#endif