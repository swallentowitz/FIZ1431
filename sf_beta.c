/* sf_beta.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <math.h>

double beta(double z, double w)
{
  double log_gamma(double);

  return exp((log_gamma(z) + log_gamma(w)) - log_gamma(z+w));
}
