#include "assignment1.h"

void shpc_ddot(
    int n,
    double *x, int incx,
    double *y, int incy,
    double *rho)
{
    *rho = 0.0;
    double *ptr_x = x;
    double *ptr_y = y;

    for (int i = 0; i < n; i++) {
        *rho += (*ptr_x) * (*ptr_y);
        ptr_x += incx;
        ptr_y += incy;
    }
}
