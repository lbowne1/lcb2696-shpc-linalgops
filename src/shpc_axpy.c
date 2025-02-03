#include "assignment1.h"

void shpc_daxpy (
    int n ,
    double *alpha,
    double *x , int incx ,
    double *y , int incy)
{
    double *ptr_y = y;
    double *ptr_x = x;

    for (int i = 0; i < n; i++) {
        *ptr_y += (*alpha) * (*ptr_x);
        ptr_y += incy;
        ptr_x += incx;
    }
}