/* main_ig_improper.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 500 
#include <math.h>
#include <stdio.h>

double ig_improper(double (*)(double), double, double, double, int, 
                   double);

int count;

double f(double x)
{
  count++;
  return M_2_SQRTPI * exp(-x * x);
}

int main(void)
{
  double res, eps;

  printf("eps\t\tresultado\t\tcounts\n");
  count = 0;
  for (eps = 1.0e-4; eps >= 1.0e-10; eps *= 0.1) {
    res = ig_improper(f, 0.0, 1.0, 0.1, 4, eps);
    printf("%e\t%13.12f\t%d\n", eps, res, count);
  }
  return 0;
}
