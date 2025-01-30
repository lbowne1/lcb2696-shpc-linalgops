#include "assignment1.h"

void shpc_ddot(
    int n,
    double *x, int incx,
    double *y, int incy,
    double *rho)
{
    *rho = 0.0;
    for (int i = 0; i < n; i++) {
        *rho += ((*(x + (i * incx)) * (*(y + (i * incy)))));
    }
}
