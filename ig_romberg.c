/* ig_romberg.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <assert.h>

/*! Polynomial extrapolation at the position x=0.0 using 
    the Neville recurrence. It assumes that for p points 
    0 is the index of the most nearest x[i]. Gives back 
    also an estimate of error dy. */
double expol_to_zero(double* x, double* y, int p, double* dy,
                     double* r, double* l)
{
  double diff, yi;
  int i, m, i_min;
  
  for (i = 0; i < p; i++) { 
    r[i] = y[i];
    l[i] = y[i];
  }
  i_min = 0;
  yi = y[i_min]; 
  
  for (m = 1; m < p; m++) {
    for (i = 0; i < p-m; i++) {
      diff = (r[i+1]-l[i]) / (x[i]-x[i+m]);
      r[i] = x[i] * diff;
      l[i] = x[i+m] * diff;
    }
    (*dy) = ( ((2*i_min) < (p-m)) ? r[i_min] : l[--i_min] );
    yi += (*dy);
  }
  return yi;
}

/*! Romberg integration of function f using extended 
    trapezoidal formula with polynomial extrapolation 
    of p data points. */
double ig_romberg(double (*f)(double), double a, double b, 
                  int p, double eps)
{
  double h, sum, x, res, err;
  int i, n, nmax;
  double *s, *hv, *r, *l; 

  assert((b > a) && (p > 1));
  
  s = malloc(p * sizeof(double));
  hv = malloc(p * sizeof(double)); 
  r = malloc(p * sizeof(double));
  l = malloc(p * sizeof(double));
  
  h = (b-a);
  nmax = 1;
  s[p-1] = h * 0.5 * (f(a) + f(b));
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
    s[i] = 0.5 * (s[i+1] + h * sum);
    hv[i] = 0.25 * hv[i+1];
    h *= 0.5;
    nmax *= 2;
    if (i > 0)
      i--;
    else {
      res = expol_to_zero(hv, s, p, &err, r, l);
      for (n = p-1; n > 0; n--) {
        s[n] = s[n-1];
        hv[n] = hv[n-1];
      }
    }   
  } while (fabs(err) > fabs(res) * eps);
  
  free(s);
  free(hv); 
  free(r);
  free(l);
  
  return res;
}
