/* ip_neville.c
      
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <math.h>
#include <assert.h>
#include <stdlib.h>

/* Polynomial interpolation using the intelligent version of the algorithm of Neville (Neville+). 
   Can it actually be done in \f$\sim N\f$?
*/
double ip_neville(double xi, double* x, double* y, int n)
{
  double *r, *l;
  double diff, diff_min, yi;
  double dx_lo, dx_hi;
  int i, m, i_min;
	
  assert(n > 0);
  
  r = malloc(n * sizeof(double));
  l = malloc(n * sizeof(double));
  
  diff_min = fabs(xi-x[0]);
  i_min = 0;
  for (i = 0; i < n; i++) {
    diff = fabs(xi-x[i]);
    if (diff < diff_min) {
      diff_min = diff;
      i_min = i;
    }
    r[i] = y[i];
    l[i] = y[i];
  }
  yi = y[i_min];
  for (m = 1; m < n; m++) {
    for (i = 0; i < n-m; i++) {
      dx_lo = x[i]-xi;
      dx_hi = x[i+m]-xi;
      diff = (r[i+1]-l[i]) / (x[i]-x[i+m]);
      r[i] = dx_lo * diff;
      l[i] = dx_hi * diff;
    }
    yi += ( ((2*i_min) < (n-m)) ? r[i_min] : l[--i_min] );
  }
	
  free(r);
  free(l); 
  return yi;
}
