/* sf_hermite.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/


#include <math.h>
#include <float.h>
#define NMAX ((int)(floor(log(DBL_MAX))))

double hermite(int n, double x)
{
  double hermite1(int, double);
  double hermite2(int, double);
	
  return ((n < NMAX) ? hermite1(n, x) : hermite2(n, x));
}
