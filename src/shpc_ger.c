#include "assignment1.h"

void shpc_dger (
    int m , int n ,
    double *x , int incx ,
    double *y , int incy ,
    double *A , int rsA , int csA)
{
    double* ptr_A = A;
    double* ptr_x = x;
    double* ptr_y = y;

    for (int i = 0; i < m; i++) {
        ptr_y = y;
        ptr_A = A + (i * rsA);
        double x_val = *(x + (i * incx));
        for (int j = 0; j< n; j++) {
            (*ptr_A) += (x_val) * (*ptr_y);
            ptr_y += incy;
            ptr_A += csA;
        }
    }
 }
