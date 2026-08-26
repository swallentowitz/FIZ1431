/* main_de_mol.cl
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 500 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define THETA_INI M_PI/1.5
#define THETADOT_INI 0.2
#define PHI_INI 0.0
#define PHIDOT_INI M_PI/20.0
#define A (PHIDOT_INI * sin(THETA_INI) * sin(THETA_INI))
#define BFUNC(x) (A * A * (x))

double V_T; /* potencial over L_z kinetic erg. */
double B;

int de_solve(double*, size_t, double, double, double, double, void (*)(double*, double*, double));
             
void f(double *dxdt, double *x, double t) 
{
  double ss, cs;
  
  /* x[0] = phi, x[1] = theta, x[2] = k */
  ss = sin(x[1]);
  cs = cos(x[1]) * ss;
  ss *= ss;
  dxdt[0] = A / ss;
  dxdt[1] = x[2];
  dxdt[2] = cs * (A * dxdt[0] - B);
}

void orientation(double *r, double *x)
{ 
  r[2] = sin(x[1]);
  r[0] = cos(x[0]) * r[2];
  r[1] = sin(x[0]) * r[2];
  r[2] = cos(x[1]);
}

void angular_momentum(double *L, double *x)
{ 
  double cottheta;
  double sphi, cphi;
  
  cottheta = 1.0 / tan(x[1]);
  sphi = sin(x[0]);
  cphi = cos(x[0]);
  L[0] = x[2] * cphi - A * sphi * cottheta;
  L[1] = x[2] * sphi + A * cphi * cottheta;
  L[2] = A;
}  
  
int main(void)
{
  double x[3];
  double r[3], L[3];
  double t, tmax, tstep;
  int min_cnt;

  tmax = 100.0;
  tstep = 0.001;

  x[0] = PHI_INI;
  x[1] = THETA_INI;
  x[2] = THETADOT_INI;
  V_T = 0.0;
  B = BFUNC(V_T);
  
  for (t = 0; t < tmax; t += tstep) {
    orientation(r, x);
    angular_momentum(L, x);
    printf("%f %f %f %f %f %f %f\n", t, 
           r[0], r[1], r[2],
           L[0], L[1], L[2]);
    min_cnt = de_solve(x, 3, t, t+tstep, 1.0e-7, 1.0e-10, f);
    if (min_cnt != 0)
      fprintf(stderr, "at t = %f - # of events h < hmin: %d\n", 
              t, min_cnt);
  }
  printf("\n\n");
  
  x[0] = PHI_INI;
  x[1] = THETA_INI;
  x[2] = THETADOT_INI;
  V_T = 0.2;
  B = BFUNC(V_T);
  
  for (t = 0; t < tmax; t += tstep) {
    orientation(r, x);
    angular_momentum(L, x);
    printf("%f %f %f %f %f %f %f\n", t, 
           r[0], r[1], r[2],
           L[0], L[1], L[2]);
    min_cnt = de_solve(x, 3, t, t+tstep, 1.0e-7, 1.0e-10, f);
    if (min_cnt != 0)
      fprintf(stderr, "at t = %f - # of events h < hmin: %d\n", 
              t, min_cnt);
  }
  
  return 0;
}
