/* ig_improper.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/


#include <math.h>
#include <assert.h>
#define EPS_FACTOR 10.0

double ig_romberg(double (*)(double), double, double, int, double);

double ig_improper(double (*f)(double), double a, double b, 
                   double dx, int p, double eps)
{
  double b_lo, b_hi;
  double res, s, err;
  double eps_internal;

  assert((b > a) && (p > 1));
  eps_internal = eps / EPS_FACTOR;
  err = 0.0;
  res = 0.0; 
  s = ig_romberg(f, a, b, p, eps_internal);
  b_lo = a;
  b_hi = b;
  do {
    res += s;
    err += fabs(s);
    b_lo = b_hi;
    b_hi += dx;  
    s = ig_romberg(f, b_lo, b_hi, p, eps_internal);
  } while (fabs(s) > (eps - eps_internal) * err);
  return res;
}
