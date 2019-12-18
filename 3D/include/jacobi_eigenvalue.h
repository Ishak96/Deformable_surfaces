#ifndef JACOBI_EIGENVALUE_H
#define JACOBI_EIGENVALUE_H

void jacobi_eigenvalue (int n, float a[], int it_max, float v[], float d[], int *it_num, int *rot_num);
void r8mat_diag_get_vector (int n, float a[], float v[]);
void r8mat_identity (int n, float a[]);

#endif