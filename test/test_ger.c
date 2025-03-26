#include "assignment1.h"

int test_ger( int nrepeats, int first, int last, int inc)
{

	int size, irep;
	int m, n;
	int csA, rsA;
    int incx, incy;

	double *A, *x, *y, *A_ref, *A_old;

    double alpha, beta;

	double t_ref = DBL_MAX;
	double t     = DBL_MAX;
	double t_start; 

	double gflops_ref, gflops;

	double diff, maxdiff = 0.0;

	alpha = beta = 1.0;
	incx = incy = 1;

	printf( "%% --------- DGER --------- \n"); 
	printf( "data_dger" );
	printf( "( %4lu, 1:6 ) = [ %5lu %5lu %8.2f %8.2f %15.4e ];\n",
						 ( unsigned long )( last - first)/inc + 1,
	        			 ( unsigned long )0,
	        			 ( unsigned long )0, 0.0, 0.0, 0.0 );
	for ( size=last; size>= first; size-=inc )
	{
    	/* we will only time cases where all three matrices are square */
		maxdiff = 0.0;
    	m = n = size;
		csA = m;

		rsA = 1;

    	A = ( double * ) malloc( csA * n * sizeof( double ) );
    	x = ( double * ) malloc( incx * m * sizeof( double ) );
    	y = ( double * ) malloc( incy * n * sizeof( double ) );
    	A_old = ( double * ) malloc( csA * n * sizeof( double ) );
    	A_ref = ( double * ) malloc( csA * n * sizeof( double ) );


		bli_drandm( 0, BLIS_DENSE, m, n, A_old, rsA, csA);
        bli_drandv( n, x, incx );
		bli_drandv( n, y, incy );


		for ( irep=0; irep<nrepeats; irep++ )
		{
			memcpy( A_ref, A_old, csA * n * sizeof( double ) );

			t_start = bli_clock();
		
			bli_dger( BLIS_NO_CONJUGATE, BLIS_NO_CONJUGATE,  
						m, n, 
                        &alpha,
						x, incx, 
                        y, incy,
                        A_ref, rsA, csA );	
			t_ref = bli_clock_min_diff( t_ref, t_start );
			
		}

		gflops_ref = 2.0 * m * n / ( t_ref * 1.0e9 );

		 
		for ( irep=0; irep<nrepeats; irep++ )
		{
			memcpy( A, A_old, csA * n * sizeof( double ) );

			t_start = bli_clock();
		
			shpc_dger( m, n, 
					    x, incx,
                        y, incy, 
                        A, rsA, csA );	
			
			t = bli_clock_min_diff( t , t_start );
			
		}

		gflops = 2.0 * m * n / ( t * 1.0e9 );
		
		diff    = shpc_maxabsdiff( m, n, A, rsA, csA, A_ref, rsA, csA );
        maxdiff = max ( diff, maxdiff );

		printf( "data_dger");
		printf( "( %4lu, 1:6 ) = [ %5lu %5lu %8.2f %8.2f %15.4e ];\n",
		        ( unsigned long )(size - first)/inc + 1,
		        ( unsigned long )m,
		        ( unsigned long )n, gflops_ref, gflops, maxdiff );



		free( A );
		free( x );
		free( y );
		free( A_old );
		free( A_ref );

	}


}