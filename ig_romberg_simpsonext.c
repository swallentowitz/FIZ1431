/* ig_romberg_simpsonext.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <assert.h>

double expol_to_zero(double*, double*, int, double*, 
                     double*, double*);

/*! Romberg integration of function f using extended Simpson 
    formula with polynomial extrapolation of p data points. */
double ig_romberg_simpsonext(double (*f)(double), double a, 
                             double b, int p, double eps)
{
  double h, sum, x, res, err;
  int i, n, nmax;
  double s, s_old;
  double *c, *hv, *r, *l; 

  assert((b > a) && (p > 1));
  
  c = malloc(p * sizeof(double));
  hv = malloc(p * sizeof(double)); 
  r = malloc(p * sizeof(double));
  l = malloc(p * sizeof(double));
  
  h = (b-a);
  nmax = 1;
  s_old = h * 0.5 * (f(a) + f(b));
  c[p-1] = s_old;
  hv[p-1] = 1.0;
  i = p-2;
  
  res = 0.0;
  err = DBL_MAX;
  
  do {
    x = a + 0.5 * h;
    sum = 0.0;
    for (n = 1; n <= nmax; n++) {
      sum += f(x);
      x += h;
    }
    s = 0.5 * (s_old + h * sum);
    c[i] = (4.0 * s - s_old) / 3.0;
    hv[i] = 0.0625 * hv[i+1];
    h *= 0.5;
    nmax *= 2;
    s_old = s;
    if (i > 0)
      i--;
    else {
      res = expol_to_zero(hv, c, p, &err, r, l);
      for (n = p-1; n > 0; n--) {
        c[n] = c[n-1];
        hv[n] = hv[n-1];
      }
    }   
  } while (fabs(err) > fabs(res) * eps);
  
  free(c);
  free(hv); 
  free(r);
  free(l);
  
  return res;
}
