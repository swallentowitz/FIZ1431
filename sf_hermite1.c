/* sf_hermite1.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 800 
#include <math.h>
#define LN_SQRT_PI (0.5 * log(M_PI))

double hermite1(int n, double x)
{
  int m;
  double g_old, g, g_new;

  g_old = 0.0;
  g = exp(- 0.5 * (x * x + LN_SQRT_PI));

  if (n > 0) {
    for (m = 1; m <= n; m++) {
      g_new = sqrt(2.0/m) * x * g - sqrt(1.0 - 1.0/m) * g_old;
      g_old = g;
      g = g_new;
    }
  }
  return g;
}
