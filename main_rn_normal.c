/* main_rn_normal.c 
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 800
#include <math.h>
#include <stdio.h>
#define IMAX 10000

double sf_erf(double);
double rand_normal(long long int*, double, double);

int main(void)
{
  long long int irnd;
  int i;
  double y;

  /* for (i = -50; i < 50; i++) {
     y = 0.05 * i;
     printf("%e %e\n", y, 0.5 * (1.0 + erf(y)));
     }
     printf("\n\n"); */

  for (i = 0; i < IMAX; i++) {
    y = rand_normal(&irnd, 1.0, 0.0);
    printf("%e\n", y);
  }

  return 0;
}
