#include "assignment1.h"

int test_dot( int nrepeats, int first, int last, int inc)
{

	int size, irep; 
	int n;                  /* dimensions */
	int incx, incy;         /* strides */

	double *x, *y;    /* data structures */
	double rho, rho_ref;

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
		rho = rho_ref = 0.0;
		incx = incy = 1;
		maxdiff = 0.0;

    	x = ( double * ) malloc( n * sizeof( double ) );
    	y = ( double * ) malloc( n * sizeof( double ) );

		bli_drandv( n, x, incx );
        bli_drandv( n, y, incy );


		for ( irep=0; irep<nrepeats; irep++ )
		{

			t_start = bli_clock();
		
			bli_ddotv( BLIS_NO_CONJUGATE, BLIS_NO_CONJUGATE,
                        n,
                        x, incx,
                        y, incy,
                        &rho_ref );	
			t_ref = bli_clock_min_diff( t_ref, t_start );
			
		}

		gflops_ref = ( 2 * n ) / ( t_ref * 1.0e9 );

		 
		for ( irep=0; irep<nrepeats; irep++ )
		{

			t_start = bli_clock();
		
			shpc_ddot( n,
						x, incx,
						y, incy,
						&rho );	
			
			t = bli_clock_min_diff( t , t_start );
			
		}

		gflops = ( 2 * n ) / ( t * 1.0e9 );
		
		diff    = fabs( rho_ref - rho );

		printf( "data_ddot");
		printf( "( %4lu, 1:6 ) = [ %5lu %8.2f %8.2f %15.4e ];\n",
		        ( unsigned long )( size - first ) / inc + 1,
		        ( unsigned long )n, gflops_ref, gflops, diff);


		free( x );
		free( y );
	}
	return 0;
}

