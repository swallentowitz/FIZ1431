/* main_sf_log_gamma.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <math.h>
#include <stdio.h>

/* Declaration, not a definition! */
double log_gamma(double);

int main(void)
{
  int n;
  double fac, lnfac;
  
  for (n = 0; n <= 175; n++) {
    lnfac = log_gamma(n+1.0);
    fac = exp(lnfac);
    printf("ln[fac(%d)] = %e \t fac(%d) = %g\n", 
      n, lnfac, n, fac);
  }
  return 0;
}
