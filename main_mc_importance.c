/* main_mc_importance.c 
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 800
#include <math.h>
#include <stdio.h>
#include <float.h>
#define N 10000
#define R 1.0
#define H 0.1
#define M 1.0
#define SIGMA 0.1
#define MR2 (M * R * R)
#define V 1

double sf_erf(double);

double rand_shuffle(long long int*);

double rand_prob(long long int* irnd, double rms)
{
  double y_lo, y_hi, y;
  double x, p;
  double tmp;
  
  x = rand_shuffle(irnd);
  rms *= M_SQRT2;
  tmp = sf_erf(1.0 / rms);

  y_hi = 1.0;
  y_lo = 0.0;
  do {
    y = 0.5 * (y_lo + y_hi);
    p = 1.0 - sf_erf((1.0 - y) / rms) / tmp;
    if (p < x) 
      y_lo = y;
    else 
      y_hi = y;
  } while (fabs((y_hi - y_lo) / (fabs(y) + DBL_MIN)) > DBL_EPSILON);
  return y;
}

double prob(double x, double rms)
{
  double tmp1, tmp2;

  tmp1 = 1.0 / (rms * M_SQRT2);
  tmp2 = (x - 1.0) * tmp1;
  tmp2 *= tmp2;

  return (2.0 * tmp1 / sqrt(M_PI)) * exp(-tmp2) / sf_erf(tmp1);
}

int main(void)
{
  long long int irnd1, irnd2;
  double x1, x2;
  double avg1, var1, err1;
  double avg2, var2, err2;
  double tmp;
  int i;

  irnd1 = 1;
  irnd2 = 1;
  avg1 = 0.0;
  var1 = 0.0;
  avg2 = 0.0;
  var2 = 0.0;
  for (i = 1; i <= N; i++) {
    x1 = rand_shuffle(&irnd1);
    tmp = MR2 * x1 * x1 * prob(x1, SIGMA/R);
    avg1 += tmp;
    var1 += (tmp * tmp);
    err1 = V * sqrt((var1 / i - avg1 * avg1 / (i*i)) / i);
    x2 = rand_prob(&irnd2, SIGMA/R);
    tmp = MR2 * x2 * x2;
    avg2 += tmp;
    var2 += (tmp * tmp);
    err2 = V * sqrt((var2 / i - avg2 * avg2 / (i*i)) / i);
    printf("%d\t%f\t%f\t%f\t%f\n", i, avg1 * V / i, err1, avg2 * V / i, err2);
  }
}
