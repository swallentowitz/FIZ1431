/* main_sf_hermite.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>
#include <math.h>

double hermite(int, double);

int main(void)
{
  int n;
  double x, erg;

  for (n = 0; n <= 12000; n += 1000) {
    for (x = 0; x <= 160.0; x += 0.002) {
      erg = hermite(n, x);
      printf("%g %g\n", x, erg);
    }
    printf("\n\n");
  }
  return 0;
}
