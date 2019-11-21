#ifndef DEFORMATION_H
#define DEFORMATION_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <superquadrics.h>
#include <deformation.h>

summit taper(summit sum, float kx, float ky, float a3);
summit bend(summit sum, float k, float alpha);
summit twist(summit sum, float n, float a1);
int taper_forme(superquadrics forme);
int bend_forme(superquadrics forme);
int twist_forme(superquadrics forme);
summit reverse_taper(summit sum, float kx, float ky, float a3);
int reverse_taper_forme(superquadrics forme);
int reverse_bend_forme(superquadrics forme);

#endif