#include "assignment1.h"

void shpc_dger (
    int m , int n ,
    double *x , int incx ,
    double *y , int incy ,
    double *A , int rsA , int csA)
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j< n; j++) {
            *(A + (rsA * i) + (csA * j)) += ((*(x + (i * incx))) * (*(y + (j * incy))));
        }
    }
 }
