/* ig_simpsonext.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/


#include <math.h>
#include <float.h>
#include <assert.h>

/*! Calculates the integral of the function f from a to b 
    with relative error eps. Uses the Simpson extended 
    formula calculating a special combination of the 
    trapezoidal extended rule. */ 
double ig_simpsonext(double (*f)(double), double a, double b, 
                     double eps)
{
  double h, s, sum, x, res, res_old;
  int n, nmax;

  assert((b > a) && (eps > 0.0));
    
  h = (b-a);
  s = h * 0.5 * (f(a) + f(b));
  res = s;
  nmax = 1;
  do {
    x = a + 0.5 * h;
    sum = 0.0;
    for (n = 1; n <= nmax; n++) {
      sum += f(x);
      x += h;
    }
    s = 0.5 * (s + h * sum);
    res_old = res;
    res = (4.0 * s - res_old) / 3.0;  /* Simpson extended */
    h *= 0.5;
    nmax *= 2;
  } while (fabs(res - res_old) > fabs(res) * eps);
  return res;
}
