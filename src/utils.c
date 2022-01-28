#include "smartcalc.h"
#include <float.h>

int equal(double a, double b)
{
	return a - b < DBL_EPSILON;
}