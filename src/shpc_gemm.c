#include "assignment1.h"

void shpc_dgemm( int m, int n, int k,                                            
                    double *A, int rsA, int csA,                                
                    double *B, int rsB, int csB,                                
                    double *C, int rsC, int csC )
{
    double* ptr_A;
    double* ptr_B;
    double* ptr_C;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int p = 0; p < k; p++) {
                C[i * rsC + j * csC] += A[i * rsA + p * csA] * B[p * rsB + j * csB];
            }
        }
    } 

    return;
}   
