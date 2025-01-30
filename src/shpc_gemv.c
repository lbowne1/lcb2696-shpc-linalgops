#include "assignment1.h"

void shpc_dgemv (
    int m , int n ,
    double *A , int rsA , int csA ,
    double *x , int incx ,
    double *y , int incy)
{
    for (int i = 0; i < m; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += ((*(A + (i * rsA) + (j * csA))) * (*(x + (j * incx))));
        }
        *(y + (i * incy)) += sum;
    }
}