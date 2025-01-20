#include "assignment1.h"

int main(int argc, char *argv[])
{
	int first, last, inc, nrepeats;

	nrepeats = 3; 

	first = 100;
	last  = 500;
	inc   = 50;
	
	test_gemm(nrepeats, first, last, inc);

}
