#ifndef DEFORMATION_H
#define DEFORMATION_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <superquadrics.h>

int taper(superquadrics forme);
int reverse_taper(superquadrics forme);
int bend(superquadrics forme);
int reverse_bend(superquadrics forme);

#endif