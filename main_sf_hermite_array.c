/* main_sf_hermite_array.c

   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>
#define NMAX 100

void hermite_array(double*, int, double);

int main(void)
{
  int n;
  double x;
  double g[NMAX];

  x = 0.0;
  hermite_array(g, NMAX, x);

  for (n = 0; n < NMAX; n++)
    printf("%d  %g\n", n, g[n]);

  return 0;
}
