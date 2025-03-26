#include "assignment1.h"

int test_dot( int nrepeats, int first, int last, int inc)
{

	int size, irep; 
	int n;                  /* dimensions */
	int incx, incy;         /* strides */

	double *x, *y;    /* data structures */
	double *rho, *rho_ref, *rho_old;
	const double alpha = 1.0;
	const double beta = 0.0;

	double t_ref = DBL_MAX;
	double t     = DBL_MAX;
	double t_start; 

	double gflops_ref, gflops;

	double diff, maxdiff = 0.0;

	printf( "%% --------- DDOT --------- \n"); 
	printf( "data_ddot" );
	printf( "( %4lu, 1:6 ) = [ %5lu %8.2f %8.2f %15.4e ];\n",
						 ( unsigned long )( last - first)/inc + 1,
	        			 ( unsigned long )0, 0.0, 0.0, 0.0 );
	for ( size=last; size>= first; size-=inc )
	{
    	/* we will only time cases where all three matrices are square */
    	n = size;

		incx = incy = 1;
		maxdiff = 0.0;

		rho = ( double * ) malloc( sizeof( double ) );
		rho_ref = ( double * ) malloc( sizeof( double ) );
		rho_old = ( double * ) malloc( sizeof( double ) );
    	x = ( double * ) malloc( incx * n * sizeof( double ) );
    	y = ( double * ) malloc( incy * n * sizeof( double ) );

		bli_drandv( n, x, incx );
        bli_drandv( n, y, incy );
		bli_drandv( 1, rho_old, 1 );

		for ( irep=0; irep<nrepeats; irep++ )
		{
			memcpy( rho_ref, rho_old, sizeof( double ));

			t_start = bli_clock();
		
			bli_ddotxv( BLIS_NO_CONJUGATE, BLIS_NO_CONJUGATE,
                        n,
						&alpha,
                        x, incx,
                        y, incy,
						&beta,
                        rho_ref );	
			t_ref = bli_clock_min_diff( t_ref, t_start );
			
		}

		gflops_ref = ( 2 * n ) / ( t_ref * 1.0e9 );

		 
		for ( irep=0; irep<nrepeats; irep++ )
		{
			memcpy( rho, rho_old, sizeof( double ));

			t_start = bli_clock();
		
			shpc_ddot( n,
						x, incx,
						y, incy,
						rho );	
			
			t = bli_clock_min_diff( t , t_start );
			
		}

		gflops = ( 2 * n ) / ( t * 1.0e9 );
		
		diff    = fabs( *rho_ref - *rho );

		printf( "data_ddot");
		printf( "( %4lu, 1:6 ) = [ %5lu %8.2f %8.2f %15.4e];\n",
		        ( unsigned long )( size - first ) / inc + 1,
		        ( unsigned long )n, gflops_ref, gflops, diff);


		free( x );
		free( y );
	}
	return 0;
}

