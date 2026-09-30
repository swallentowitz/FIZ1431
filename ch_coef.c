/* ch_coef.c 
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 500 
#include <math.h>
#include <stdlib.h>

/*! Calculates the Chebyshev coeficients 'c[0], ..., c[n-1]' 
    for the funcion 'f' being defined in the interval 
    ['a','b']. */
void chebyshev_coef(double (*f)(double), double a, double b, 
                    double* c, int n)
{
  int k, j;
  double bma, bpa, fac, tmp, *value;
  
  value = malloc(n * sizeof(double));
  bma = 0.5 * (b - a);
  bpa = 0.5 * (b + a);
  for (k = 0; k < n; k++) {
    tmp = cos(M_PI * (k + 0.5) / n);
    value[k] = f(tmp * bma + bpa);
  }
  fac = 2.0 / n;
  for (j = 0; j < n; j++) {
    tmp = 0.0;
    for (k = 0; k < n; k++)
      tmp += value[k] * cos(M_PI * j * (k + 0.5) / n);
    c[j] = fac * tmp;		
  }
  free(value);
}

