#include "assignment1.h"

void shpc_dgemm( int m, int n, int k,                                            
                    double *A, int rsA, int csA,                                
                    double *B, int rsB, int csB,                                
                    double *C, int rsC, int csC )
{
    double* A_ptr = A;
    double* B_ptr = B;
    double* C_ptr = C;

    for (int row = 0; row < m; row++) {
        A_ptr = A + (row * rsA * sizeof(double));
        for (int col = 0; col < n; col++) {
            B_ptr = B + (col * csB * sizeof(double));
            int sum = 0;
            for (int ele = 0; ele < k; ele++) {
                sum += (*A_ptr * *B_ptr);
                A_ptr += (csA * sizeof(double));
                B_ptr += (rsB * sizeof(double));
            }
            C_ptr = (row * rsC * sizeof(double)) + (col * csC * sizeof(double));
            *C_ptr = sum;
        }
    } 

    free(A_ptr);
    free(B_ptr);
    free(C_ptr);

    return;
}   
