/* sf_log_gamma.c 
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

/* This enables math constants like M_SQRT2 */
#define _XOPEN_SOURCE 800 
#include <math.h>

double log_gamma(double x)
{
  double erg;
  double tmp;
  int n;
  static double s = 2.0 * M_SQRT2 / M_2_SQRTPI;
  static double c[7] = {1.000000000190015, 
    76.18009172947146, -86.50532032941677, 
    24.01409824083091, -1.231739572450155, 
    0.1208650973866179e-2, -0.5395239384953e-5};
    
  tmp = x + 5.5;
  erg = (x + 0.5) * log(tmp) - tmp;
  tmp = c[0];
  for (n = 1; n < 7; n++)
    tmp += c[n] / (x + n);
  return erg + log(s * tmp / x);
}
