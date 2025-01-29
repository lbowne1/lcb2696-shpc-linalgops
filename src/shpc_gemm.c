#include "assignment1.h"

void shpc_dgemm( int m, int n, int k,                                            
                    double *A, int rsA, int csA,                                
                    double *B, int rsB, int csB,                                
                    double *C, int rsC, int csC )
{
    double* A_ptr = A;
    double* B_ptr = B;
    double* C_ptr = C;

    for (int i = 0; i < m; i++) {
        A_ptr = A + (i * rsA);
        for (int j = 0; j < n; j++) {
            B_ptr = B + (j * csB);
            int sum = 0;
            for (int p = 0; p < k; p++) {
                sum += (*A_ptr * *B_ptr);
                A_ptr += csA;
                B_ptr += rsB;
            }
            C_ptr = (C + i * rsC + j * csC);
            *C_ptr += sum;
        }
    } 

    return;
}   
