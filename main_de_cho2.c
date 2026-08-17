/* main_de_cho2.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SZ 4
#define GAMMA1 0.1
#define OMEGA1 1.0
#define X_INI1 1.0
#define P_INI1 0.0
#define GAMMA2 0.1
#define OMEGA2 8.0
#define X_INI2 1.0
#define P_INI2 0.0
#define KAPPA1 1.0
#define KAPPA2 0.05
#define OMEGA1SQR (OMEGA1 * OMEGA1)
#define OMEGA2SQR (OMEGA2 * OMEGA2)

int de_solve(double*, size_t, double, double, double, double, 
             void (*)(double*, double*, double));

void f(double *dxdt, double *x, double t) 
{
  /* 2 coupled, damped harmonic oscillators */
  dxdt[0] = x[1];
  dxdt[1] = - OMEGA1SQR * x[0] - GAMMA1 * x[1] + KAPPA1 * x[2];
  dxdt[2] = x[3];
  dxdt[3] = KAPPA2 * x[0] - OMEGA2SQR * x[2] - GAMMA2 * x[3];
}
  
int main(void)
{
  double x[SZ];
  double t, tmax, tstep;
  int min_cnt;

  tmax = 40.0;
  tstep = 0.01;

  x[0] = X_INI1;
  x[1] = P_INI1;
  x[2] = X_INI2;
  x[3] = P_INI2;
  
  for (t = 0; t < tmax; t += tstep) {
    printf("%f %f %f %f %f\n", t, x[0], x[1], x[2], x[3]);
    min_cnt = de_solve(x, SZ, t, t+tstep, 1.0e-7, 1.0e-10, f);
    if (min_cnt != 0)
      fprintf(stderr, "at t = %f - # of events h < hmin: %d\n", 
              t, min_cnt);
  }
  return 0;
}
