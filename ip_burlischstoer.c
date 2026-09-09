/* ip_burlischstoer.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <assert.h>

/*! Calculates a rational interpolation using the recursion
    of Burlisch & Stoer. */
double ip_burlischstoer(double xi, double* x, double* y, int n)
{
  double *r, *l;
  double diff, diff_min, yi;
  double ratio, factor;
  int i, m, i_min;
  
  assert(n > 0);
  
  r = malloc(n * sizeof(double));
  l = malloc(n * sizeof(double));
  
  diff_min = fabs(xi-x[0]);
  i_min = 0;
  for (i = 0; i < n; i++) {
    diff = fabs(xi-x[i]);
    if (diff == 0.0) {
      free(r);
      free(l);
      return y[i];
    }
    else if (diff < diff_min) {
      diff_min = diff;
      i_min = i;
    }
    r[i] = y[i];
    l[i] = y[i]; /* + DBL_MIN; */
  }
  yi = y[i_min];
  for (m = 1; m < n; m++) {
    for (i = 0; i < n-m; i++) {
      ratio = (xi-x[i])/(xi-x[i+m]) * l[i];
      factor = ratio - r[i+1];
      factor = (fabs(factor) < DBL_MIN) ? DBL_MIN : factor; 
      factor = (r[i+1]-l[i])/factor;
      l[i] = r[i+1] * factor;
      r[i] = ratio * factor;
    }
    yi += ( ((2*i_min) < (n-m)) ? r[i_min] : l[--i_min] );
  }
  free(r);
  free(l);
  return yi;
}
