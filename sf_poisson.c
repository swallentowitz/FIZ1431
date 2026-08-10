/* sf_poisson.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <math.h>

double poisson(double n, double navg)
{
  double log_gamma(double);	/* Declaration */

  return exp(n * log(navg) - log_gamma(n+1.0) - navg);
}


