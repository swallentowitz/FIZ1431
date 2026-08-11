/* main_sf_hermite1.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>
#include <math.h>

double hermite1(int, double);

int main(void)
{
  int n;
  double x, erg;

  for (n = 0; n <= 800; n += 100) {
    for (x = 0; x <= 50.0; x += 0.002) {
      erg = hermite1(n, x);
      printf("%g %g\n", x, erg);
    }
    printf("\n\n");
  }
  return 0;
}
