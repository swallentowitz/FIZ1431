/* main_sf_bibe.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>

double bico(double, double);
double beta(double, double);

int main(void)
{
  int m, n;
  double res_bi, res_be;

  m = 20;
  for (n = 0; n <= m; n++) {
    res_bi = bico(m, n);
    res_be = beta(m, n);   /* not defined for n = 0 */
    printf("%d %g %g\n", n, res_bi, res_be);
  }
  return 0;
}
