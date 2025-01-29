#include "assignment1.h"

void shpc_dgemm( int m, int n, int k,                                            
                    double *A, int rsA, int csA,                                
                    double *B, int rsB, int csB,                                
                    double *C, int rsC, int csC )
{
    double* A_ptr;
    double* B_ptr;
    double* C_ptr;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0;
            double* A_ptr = A + (i * rsA);
            double* B_ptr = B + (j * csB);

            for (int p = 0; p < k; p++) {
                sum += (*A_ptr) * (*B_ptr);
                A_ptr += csA;
                B_ptr += rsB;
            }

            C[(i * rsC) + (j * csC)] = sum; 
        }
    } 

    return;
}   
