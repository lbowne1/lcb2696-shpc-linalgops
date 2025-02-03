#include "assignment1.h"

void shpc_dgemv (
    int m , int n ,
    double *A , int rsA , int csA ,
    double *x , int incx ,
    double *y , int incy)
{
    double* ptr_A = A;
    double* ptr_x = x;
    double* ptr_y = y;

    for (int i = 0; i < m; i++) {
        ptr_A = A + ( i * rsA );
        ptr_x = x;
        for (int j = 0; j < n; j++) {
            *ptr_y += (*ptr_A) * (*ptr_x);
            ptr_A += csA;
            ptr_x += incx;
        }
        ptr_y += incy;
    }
}