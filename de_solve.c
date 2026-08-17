/* de_solve.c 
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <complex.h>
#define SAFETY_FACTOR 0.9

/* Solves an ODE using adaptive stepsizes with the embedded RK 
   method. Integrate starting values y[0..sz-1] from t1 to t2 
   with (relative) accuracy eps. dtmin is the minimum allowed 
   stepsize (can be zero). y[..] is replaced by values at the 
   end of the integration interval. "f()" is the user-supplied 
   routine for calculating the right-hand side derivative. */
int de_solve(double *y, size_t sz, double t1, double t2, 
             double eps, double dtmin, 
             void (*f)(double*, double*, double))
{
  double rk_embedded(double*, double, size_t, double, double*, 
                   void (*)(double*, double*, double)); 
  size_t i;
  double t, dt, err, *ytmp;
  int min_cnt;

  dt = t2 - t1;
  assert((dtmin >= 0.0) && (dt >= dtmin));
  ytmp = malloc(sz * sizeof(double));
  t = t1;
  min_cnt = 0; 
  
  do {
    for(;;) {
      dt = ((t+dt) > t2) ? t2-t : dt;
      err = rk_embedded(y, t, sz, dt, ytmp, f);
      err /= eps;
      if (err > 1.0) {
        dt *= SAFETY_FACTOR * pow(err, -0.2);
        if (dt < dtmin) {
          min_cnt++;
          dt = dtmin;
        }
      } else {
        t += dt;
        dt *= SAFETY_FACTOR * pow(err, -0.2);
        for (i = 0; i < sz; i++) 
          y[i] = ytmp[i];
        break;
      }
    }
  } while ((t2-t) > DBL_MIN);
  free(ytmp);
  return min_cnt;
}

/* Solves an ODE using adaptive stepsizes with the embedded RK 
   method. Integrate starting values y[0..sz-1] from t1 to t2 
   with (relative) accuracy eps. dtmin is the minimum allowed 
   stepsize (can be zero). y[..] is replaced by values at the 
   end of the integration interval. "f()" is the user-supplied 
   routine for calculating the right-hand side derivative. 
   Complex version. */
int de_solve_cpx(complex double *y, size_t sz, double t1, 
                 double t2, double eps, double dtmin, 
                 void (*f)(complex double*, complex double*, 
                           double))
{
  double rk_embedded_cpx(complex double*, double, size_t, 
           double, complex double*, 
           void (*)(complex double*, complex double*, double)); 
  size_t i;
  double t, dt, err;
  complex double *ytmp;
  int min_cnt;

  dt = t2 - t1;
  assert((dtmin >= 0.0) && (dt >= dtmin));
  ytmp = malloc(sz * sizeof(complex double));
  t = t1;
  min_cnt = 0; 
  
  do {
    for(;;) {
      dt = ((t+dt) > t2) ? t2-t : dt;
      err = rk_embedded_cpx(y, t, sz, dt, ytmp, f);
      err /= eps;
      if (err > 1.0) {
        dt *= SAFETY_FACTOR * pow(err, -0.2);
        if (dt < dtmin) {
          min_cnt++;
          dt = dtmin;
        }
      } else {
        t += dt;
        dt *= SAFETY_FACTOR * pow(err, -0.2);
        for (i = 0; i < sz; i++) 
          y[i] = ytmp[i];
        break;
      }
    }
  } while ((t2-t) > DBL_MIN);
  free(ytmp);
  return min_cnt;
}

