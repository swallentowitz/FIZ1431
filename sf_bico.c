/* sf_bico.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <math.h>

double bico(double m, double n)
{
  double log_gamma(double);

  return exp(log_gamma(m+1.0) - (log_gamma(n+1.0) + log_gamma(m-n+1.0)));
}
