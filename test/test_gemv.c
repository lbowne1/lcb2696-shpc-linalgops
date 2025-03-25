#include "assignment1.h"

int test_gemv( int nrepeats, int first, int last, int inc)
{

	int size, irep;
	int m, n;
	int csA;
	int rsA;
    int incx, incy;

	double *A, *x, *y, *y_ref, *y_old;

    const double alpha = 1.0, beta = 1.0;


	double t_ref = DBL_MAX;
	double t     = DBL_MAX;
	double t_start; 

	double gflops_ref, gflops;

	double diff, maxdiff = 0.0;

	incx = incy = 1;

	printf( "%% --------- DGEMV --------- \n"); 
	printf( "data_dgemv" );
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
    	x = ( double * ) malloc( incx * n * sizeof( double ) );
    	y = ( double * ) malloc( incy * n * sizeof( double ) );
    	y_ref = ( double * ) malloc( incy * n * sizeof( double ) );
    	y_old = ( double * ) malloc( incy * n * sizeof( double ) );


		bli_drandm( 0, BLIS_DENSE, m, n, A, rsA, csA);
		bli_drandv( n, x, incx );
		bli_drandv( n, y_old, incy );


		for ( irep=0; irep<nrepeats; irep++ )
		{
			memcpy( y_ref, y_old, ( n * sizeof( double ) ) );

			t_start = bli_clock();
		
			bli_dgemv( BLIS_NO_TRANSPOSE, BLIS_NO_CONJUGATE,  
						m, n,
                        &alpha, 
						A, rsA, csA, 
						x, incx, 
						&beta,
                        y_ref, incy );	
			t_ref = bli_clock_min_diff( t_ref, t_start );
			
		}

		gflops_ref = 2 * m * n / ( t_ref * 1.0e9 );

		 
		for ( irep=0; irep<nrepeats; irep++ )
		{
			memcpy( y, y_old, ( n * sizeof( double ) ) );

			t_start = bli_clock();
		
			shpc_dgemv( m, n, 
						A, rsA, csA, 
						x, incx, 
					    y, incy );	
			
			t = bli_clock_min_diff( t , t_start );
			
		}

		gflops = 2 * m * n / ( t * 1.0e9 );
		
		diff    = shpc_maxabsdiff( n, 1, y, incy, 0, y_ref, incy, 0 );
        maxdiff = max ( diff, maxdiff );

		printf( "data_dgemv");
		printf( "( %4lu, 1:6 ) = [ %5lu %5lu %8.2f %8.2f %15.4e ];\n",
		        ( unsigned long )(size - first)/inc + 1,
		        ( unsigned long )m,
		        ( unsigned long )n, gflops_ref, gflops, maxdiff );



		free( A );
		free( x );
		free( y );
		free( y_old );
		free( y_ref );

	}


}