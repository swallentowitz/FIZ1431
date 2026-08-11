/* sf_hermite_array.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/


#define _XOPEN_SOURCE 500 
#include <math.h>
#define LN_SQRT_PI (0.5 * log(M_PI))

/*! Calculates Hermite array h[0], h[1], ... ,h[nmax-1]
    for the x value given. */
void hermite_array(double* h, int nmax, double x)
{
  int n;
  long double g, g_old, g_new;

  g_old = 0.0;
  g = expl(- 0.5 * (x * x + LN_SQRT_PI));
  h[0] = (double)g;
  if (nmax > 1) {
    for (n = 1; n < nmax; n++) {
      g_new = sqrt(2.0/n) * x * g - sqrt(1.0 - 1.0/n) * g_old;
      g_old = g;
      g = g_new;
      h[n] = (double)g;
    }
  }
}

