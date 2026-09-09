/* ip_ratlocal.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <assert.h>

/*! Calculates a local rational interpolation using p data
    points from the vector of n data. Uses the recurrence
    by Burlisch & Stoer. */
double ip_ratlocal(double xi, int p, double* x, double* y, 
                   int n)
{
  int pos;
  int searchidx(double, double*, int);
  double ip_burlischstoer(double, double*, double*, int);
  
  assert((n > 0) && (xi >= x[0]) && (xi <= x[n-1]));

  pos = searchidx(xi, x, n) - p/2 + 1; 
  pos = (pos < 0) ? 0 : pos; /* ensure pos >= 0 */
  pos = (pos > (n-p)) ? (n-p) : pos; /* ensure pos+p <= n */
  return ip_burlischstoer(xi, &(x[pos]), &(y[pos]), p);   
}
