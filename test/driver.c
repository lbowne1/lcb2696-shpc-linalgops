#include "assignment1.h"

int main(int argc, char *argv[])
{
	int first, last, inc, nrepeats;
    
    int err = get_args( argc, argv, &nrepeats, &first, &last, &inc );
    if ( err != 0 ) return 1;
    	
	test_dot(nrepeats, first, last, inc);
    test_axpy(nrepeats, first, last, inc);
    test_gemv(nrepeats, first, last, inc);
    test_ger(nrepeats, first, last, inc);
    test_gemm(nrepeats, first, last, inc);

}
