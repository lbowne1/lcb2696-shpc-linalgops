#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>


#define dabs( x ) ( (x) < 0 ? -(x) : x )
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define _XOPEN_SOURCE 


#include "blis.h"

#include "src.h"
#include "test.h"                                                        
#include "util.h"
