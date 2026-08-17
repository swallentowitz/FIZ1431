/* de_rkembedded.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <complex.h>
/* Cash-Karp constants: */
static const double a2 = 0.2, a3 = 0.3, a4 = 0.6, 
  a5 = 1.0, a6 = 0.875;
static const double b21 = 0.2, b31 = 3.0/40.0, 
  b32 = 9.0/40.0, b41 = 0.3, b42 = -0.9, b43 = 1.2, 
  b51 = -11.0/54.0, b52=2.5, b53 = -70.0/27.0, 
  b54 = 35.0/27.0, b61 = 1631.0/55296.0, 
  b62 = 175.0/512.0, b63 = 575.0/13824.0, 
  b64 = 44275.0/110592.0, b65 = 253.0/4096.0;
static const double c1 = 37.0/378.0, c3 = 250.0/621.0, 
  c4 = 125.0/594.0, c6 = 512.0/1771.0;
static const double dc1 = 37.0/378.0 - 2825.0/27648.0, 
  dc3 = 250.0/621.0 - 18575.0/48384.0,
  dc4 = 125.0/594.0 - 13525.0/55296.0, 
  dc5 = -277.0/14336.0,
  dc6 = 512.0/1771.0 - 0.25;

/*! Given values for sz variables x[0..sz-1] known at x, 
    use the fifth-order Cash-Karp Runge-Kutta method to 
    advance the solution over an interval dt and return 
    the incremented variables as xout[0..sz-1]. Also return 
    an estimate of the maximal relative error in xout using 
    the embedded fourth-order method. The user supplies 
    the routine f(dxdt, x, t), which returns derivatives 
    dx/dt at t. */
double rk_embedded(double *x, double t, size_t sz, double dt, 
                   double *xout, 
                   void (*f)(double*, double*, double))
{
  int i;
  double *k1, *k2, *k3, *k4, *k5, *k6;
  double err_max, err_tmp;
  
  k1 = malloc(sz * sizeof(double));
  k2 = malloc(sz * sizeof(double));
  k3 = malloc(sz * sizeof(double));
  k4 = malloc(sz * sizeof(double));
  k5 = malloc(sz * sizeof(double));
  k6 = malloc(sz * sizeof(double));

  f(k1, x, t);

  for (i = 0; i < sz; i++)
    xout[i] = x[i] + b21 * dt * k1[i];
  f(k2, xout, t + a2 * dt);
  
  for (i = 0; i < sz; i++)
    xout[i] = x[i] + dt * (b31 * k1[i] + b32 * k2[i]);
  f(k3, xout, t + a3 * dt);

  for (i = 0; i < sz; i++)
    xout[i] = x[i] + dt * (b41 * k1[i] + b42 * k2[i] 
      + b43 * k3[i]);
  f(k4, xout, t + a4 * dt);

  for (i = 0; i < sz; i++)
    xout[i] = x[i] + dt * (b51 * k1[i] + b52 * k2[i] 
      + b53 * k3[i] + b54 * k4[i]);
  f(k5, xout, t + a5 * dt);

  for (i = 0; i < sz; i++)
    xout[i] = x[i] + dt * (b61 * k1[i] + b62 * k2[i] 
      + b63 * k3[i] + b64 * k4[i] + b65 * k5[i]);
  f(k6, xout, t + a6 * dt);
  
  err_max = 0.0;
  for (i = 0; i < sz; i++) {
    xout[i] = x[i] + dt * (c1 * k1[i] + c3 * k3[i] 
      + c4 * k4[i] + c6 * k6[i]);
    err_tmp = fabs(dt * (dc1 * k1[i] + dc3 * k3[i] 
      + dc4 * k4[i] + dc5 * k5[i] + dc6 * k6[i])) 
      / (fabs(xout[i]) + DBL_MIN);
    err_max = (err_max > err_tmp) ? err_max : err_tmp;
  }

  free(k1);
  free(k2);
  free(k3);
  free(k4);
  free(k5);
  free(k6);
  return err_max;
}


/*! Given values for sz variables x[0..sz-1] known at x, 
    use the fifth-order Cash-Karp Runge-Kutta method to 
    advance the solution over an interval dt and return 
    the incremented variables as xout[0..sz-1]. Also return 
    an estimate of the maximal relative error in xout using 
    the embedded fourth-order method. The user supplies 
    the routine f(dxdt, x, t), which returns derivatives 
    dx/dt at t. Complex version. */
double rk_embedded_cpx(complex double *x, double t, size_t sz, 
           double dt, complex double *xout, 
           void (*f)(complex double*, complex double*, double))
{
  int i;
  complex double *k1, *k2, *k3, *k4, *k5, *k6;
  double err_max, err_tmp;
  
  k1 = malloc(sz * sizeof(complex double));
  k2 = malloc(sz * sizeof(complex double));
  k3 = malloc(sz * sizeof(complex double));
  k4 = malloc(sz * sizeof(complex double));
  k5 = malloc(sz * sizeof(complex double));
  k6 = malloc(sz * sizeof(complex double));

  f(k1, x, t);

  for (i = 0; i < sz; i++)
    xout[i] = x[i] + b21 * dt * k1[i];
  f(k2, xout, t + a2 * dt);
  
  for (i = 0; i < sz; i++)
    xout[i] = x[i] + dt * (b31 * k1[i] + b32 * k2[i]);
  f(k3, xout, t + a3 * dt);

  for (i = 0; i < sz; i++)
    xout[i] = x[i] + dt * (b41 * k1[i] + b42 * k2[i] 
      + b43 * k3[i]);
  f(k4, xout, t + a4 * dt);

  for (i = 0; i < sz; i++)
    xout[i] = x[i] + dt * (b51 * k1[i] + b52 * k2[i] 
      + b53 * k3[i] + b54 * k4[i]);
  f(k5, xout, t + a5 * dt);

  for (i = 0; i < sz; i++)
    xout[i] = x[i] + dt * (b61 * k1[i] + b62 * k2[i] 
      + b63 * k3[i] + b64 * k4[i] + b65 * k5[i]);
  f(k6, xout, t + a6 * dt);
  
  err_max = 0.0;
  for (i = 0; i < sz; i++) {
    xout[i] = x[i] + dt * (c1 * k1[i] + c3 * k3[i] 
      + c4 * k4[i] + c6 * k6[i]);
    err_tmp = cabs(dt * (dc1 * k1[i] + dc3 * k3[i] 
      + dc4 * k4[i] + dc5 * k5[i] + dc6 * k6[i])) 
      / (cabs(xout[i]) + DBL_MIN);
    err_max = (err_max > err_tmp) ? err_max : err_tmp;
  }

  free(k1);
  free(k2);
  free(k3);
  free(k4);
  free(k5);
  free(k6);
  return err_max;
}
