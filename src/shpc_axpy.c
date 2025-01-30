#include "assignment1.h"

void shpc_daxpy (
    int n ,
    double * alpha ,
    double *x , int incx ,
    double *y , int incy)
{
    for (int i = 0; i < n; i++) {
        *(y + (i * incy)) += ((*alpha) * (*(x + (i * incx))));
    }
}