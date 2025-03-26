#include "assignment1.h"

int test_axpy( int nrepeats, int first, int last, int inc)
{

	int size, irep;
	int n;
	int incx, incy;

	double *x, *y, *y_ref, *y_old;
	double *alpha;


	double t_ref = DBL_MAX;
	double t     = DBL_MAX;
	double t_start; 

	double gflops_ref, gflops;

	double diff, maxdiff = 0.0;
	incx = incy = 1;

	printf( "%% --------- DAXPY --------- \n"); 
	printf( "data_daxpy" );
	printf( "( %4lu, 1:6 ) = [ %5lu %8.2f %8.2f %15.4e ];\n",
						 ( unsigned long )( last - first)/inc + 1,
	        			 ( unsigned long )0, 0.0, 0.0, 0.0 );
	for ( size=last; size>= first; size-=inc )
	{
    	/* we will only time cases where all three matrices are square */
    	n = size;

    	x = ( double * ) malloc( incx * n * sizeof( double ) );
    	y = ( double * ) malloc( incy * n * sizeof( double ) );
    	y_ref = ( double * ) malloc( incy * n * sizeof( double ) );
    	y_old = ( double * ) malloc( incy * n * sizeof( double ) );
		alpha = ( double * ) malloc( sizeof( double ) );

		bli_drandv( n, x, incx );
        bli_drandv( n, y_old, incy );
		bli_drandv( 1, alpha, 1 );

		maxdiff = 0.0;

		for ( irep=0; irep<nrepeats; irep++ )
		{
			memcpy( y_ref, y_old, ( incy * n * sizeof( double ) ) );

			t_start = bli_clock();
		
			bli_daxpyv( BLIS_NO_CONJUGATE,
                        n,
                        alpha,
                        x, incx,
                        y_ref, incy );	
			t_ref = bli_clock_min_diff( t_ref, t_start );
			
		}

		gflops_ref = 2.0 * n / ( t_ref * 1.0e9 );

		 
		for ( irep=0; irep<nrepeats; irep++ )
		{
			memcpy( y, y_old, ( n * sizeof( double ) ) );

			t_start = bli_clock();
		
			shpc_daxpy( n,
                        alpha,
						x, incx,
						y, incy );	
			
			t = bli_clock_min_diff( t , t_start );
			
		}

		gflops = 2.0 * n / ( t * 1.0e9 );
		
		diff    = shpc_maxabsdiff( n, 1, y, incy, 0, y_ref, incy, 0 );
        maxdiff = max ( diff, maxdiff );

		printf( "data_daxpy");
		printf( "( %4lu, 1:6 ) = [ %5lu %8.2f %8.2f %15.4e];\n",
		        ( unsigned long )(size - first)/inc + 1,
		        ( unsigned long )n, gflops_ref, gflops, maxdiff );


		free( x );
		free( y );
		free( y_ref );
		free( y_old );

	}
}

