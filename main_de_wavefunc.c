/* main_de_wavefunc.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 500 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#define SZ 200
#define A 0.02
#define F 0.0
#define OMEGA_F 1.0 
#define R 2.0
#define PHI (0.1 * M_PI)
/* for printing */
#define X 7.0
#define N 150

double poisson(double, double);
complex double wavefunction(double x, complex double*, size_t);
int de_solve_cpx(complex double*, size_t, double, double, double, double, 
                 void (*)(complex double*, complex double*, double));

/*! Calculates initial state as coherent state of
    amplitude R * exp(I*PHI). */
void calc_ini(complex double* psi)
{
  size_t n;
  double res, tmp;
  
  res = 0.0;
  for (n = 0; n < SZ; n++) {
    psi[n] = cexp(n * PHI * I) * sqrt(poisson(n, R*R));
    tmp = cabs(psi[n]);
    res += tmp * tmp;
  }
  if (fabs(res-1.0) > 1.0e-5)
    fprintf(stderr, "R too large!\n");
}

/*! Calculates the external force of the form
    F * cos(OMEGA_F * t). */
double force(double t)
{
  return F * cos(OMEGA_F * t);
}
                 
void f(complex double *dpsidt, complex double *psi, double t) 
{
  size_t n;
  /* all is rotating with exp[-i (0.5 + 3.0 * A)t] */
  for (n = 0; n < SZ; n++) {
    dpsidt[n] = - I * ( (n + 6.0 * A * n * (n+1.0)) * psi[n]
      + ((n < 1) ? 0.0 : ( force(t) * sqrt(n) * psi[n-1] )) 
      + ((n < 2) ? 0.0 : ( 2.0 * A * (2.0 * n - 1.0) * sqrt(n * (n-1.0)) * psi[n-2]))
      + ((n < 4) ? 0.0 : (A * sqrt(n * (n-1.0) * (n-2.0) * (n-3.0)) * psi[n-4]))
      + ((n > (SZ-5)) ? 0.0 : (A * sqrt((n+4.0) * (n+3.0) * (n+2.0) * (n+1.0)) * psi[n+4])) 
      + ((n > (SZ-3)) ? 0.0 : (2.0 * A * (2.0 * n + 3.0) * sqrt((n+2.0) * (n+1.0)) * psi[n+2]))
      + ((n > (SZ-2)) ? 0.0 : ( force(t) * sqrt(n+1) * psi[n+1])) );
  } 
}
  
/*! Checks for overflow problems in the state vector. */
int overflow(complex double* psi, unsigned offset, double limit)
{
  size_t n;
  double tmp;
  
  for (n = SZ-offset-1; n < SZ; n++) {
    tmp = cabs(psi[n]);
    limit -= tmp * tmp;
  }
  return ((limit < 0.0) ? 1 : 0);
}

/*! Calculates the norm of the state. */
double norm(complex double* psi)
{
  size_t n;
  double res, tmp;
  
  res = 0.0;
  for (n = 0; n < SZ; n++) {
    tmp = cabs(psi[n]);
    res += tmp * tmp;
  }
  return res;
}

/*! Prints the modulus square of the wavefunction. */
void print_probability(complex double* psi)
{
  double x, dx, prob;
  complex double psix;
  int i;
  
  dx = 2.0 * X / N;
  x = -X;
  for (i = 0; i < N; i++) {
    psix = wavefunction(x, psi, SZ);
    prob = cabs(psix);
    prob *= prob;
    printf("%f %f\n", x, prob);
    x += dx;
  }
  printf("\n\n\n");
}
  

int main(void)
{
  complex double psi[SZ];
  double t, tmax, tstep, tmp;
  int min_cnt;

  tmax = 24.0;
  tstep = 0.05;
  
  calc_ini(psi);
  for (t = 0; t < tmax; t += tstep) {
    printf("# t = %f\n", t);
    print_probability(psi);
    min_cnt = de_solve_cpx(psi, SZ, t, t+tstep, 1.0e-7, 1.0e-10, f);
    if (min_cnt != 0)
      fprintf(stderr, "# at t = %f, (# of counts of h < hmin) = %d\n", t, min_cnt);
    if (overflow(psi, 10, 0.01))
      fprintf(stderr, "# at t = %f, population in last 10 levels too high!\n", t);
    tmp = norm(psi);
    if (fabs(tmp-1.0) > 1.0e-5)
      fprintf(stderr, "# at t = %f, norm = %f\n", t, tmp);
  }
  return 0;
}
