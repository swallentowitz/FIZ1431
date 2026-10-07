/* rn_normal.c 
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 800
#include <math.h>
#include <float.h>
#include <stdio.h>
#define SAFETY 500

double rand_shuffle(long long int*);

double sf_erf(double x)
{
  const double a[4] = {0.278393, 0.230389, 0.000972, 0.078108};
  double tmp, y;

  y = fabs(x);
  tmp = 1.0 / (1.0 + (a[0] + (a[1] + (a[2] + a[3] * y ) * y ) * y ) * y);
  tmp *= tmp;
  tmp = 1.0 - tmp * tmp;
  tmp = ((x >= 0.0) ? tmp : (-tmp));
  return tmp;
}

double rand_normal(long long int* irnd, double rms, double avg)
{
  double y_lo, y_hi, y;
  double x, p;
  
  x = rand_shuffle(irnd);
  rms *= M_SQRT2;

  y_hi = SAFETY * rms;
  y_lo = - y_hi;
  do {
    y = 0.5 * (y_lo + y_hi);
    p = 0.5 * (1.0 + sf_erf(y / rms));
    if (p < x) 
      y_lo = y;
    else 
      y_hi = y;
  } while (fabs((y_hi - y_lo) / (fabs(y) + DBL_MIN)) > DBL_EPSILON);
  return y + avg;
}
