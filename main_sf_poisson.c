/* main_sf_poisson.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>

double poisson(double, double);

int main(void)
{
  int n;
  double navg, erg;
  
  navg = 700.6;
  for (n = 600; n <= 800; n++) {
    erg = poisson(n, navg);
    printf("%d  %g\n", n, erg);
  }
  return 0;
}
