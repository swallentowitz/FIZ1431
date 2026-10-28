/* ft_step.c
     
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 500 
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <assert.h>
#include <float.h>
#define SAFETY_FACTOR 0.9

void fft(complex double*, size_t, int);

double splitstep(complex double* in, double t, size_t bits, double dt,
		 complex double* out, double (*f)(double, double),
		 double kc, double kappa)
{
  double dq, dk, err;
  size_t m, N;
  complex double *expk, *expv, *out2;

  N = (1 << bits);
  expk = malloc(N * sizeof(complex double));
  expv = malloc(N * sizeof(complex double));
  out2 = malloc(N * sizeof(complex double));
  
  dq = 1.0 / (2.0 * kc);
  dk = 2.0 * kc / N;
  
  for (m = 0; m <= N/2; m++) {
    expk[m] = cexp(-I * 0.5 * M_PI * M_PI * dt * dk  * dk * m * m);
    out[m] = in[m] * expk[m] * expk[m];
  }
  for (m = N/2+1; m < N; m++) 
    out[m] = in[m] * expk[abs(m-N)] * expk[abs(m-N)];
  fft(out, bits, -1);
  for (m = 0; m < N; m++) {
    expv[m] = cexp(-I * 0.5 * dt * f(dq * (kappa + m), t));
    out[m] *= expv[m] * expv[m];
  }
  fft(out, bits, +1);
  for (m = 0; m <= N/2; m++)
    out[m] *= expk[m] * expk[m] / N;
  for (m = N/2+1; m < N; m++) 
    out[m] *= expk[abs(m-N)] * expk[abs(m-N)] / N;

  /* two steps */
  for (m = 0; m <= N/2; m++) 
    out2[m] = in[m] * expk[m];
  for (m = N/2+1; m < N; m++) 
    out2[m] = in[m] * expk[abs(m-N)];
  fft(out2, bits, -1);
  for (m = 0; m < N; m++) 
    out2[m] *= expv[m];
  fft(out2, bits, +1);
  for (m = 0; m <= N/2; m++)
    out2[m] *= expk[m] / N;
  for (m = N/2+1; m < N; m++) 
    out2[m] *= expk[abs(m-N)] / N;

  for (m = 0; m <= N/2; m++) 
    out2[m] *= expk[m];
  for (m = N/2+1; m < N; m++) 
    out2[m] *= expk[abs(m-N)];
  fft(out2, bits, -1);
  for (m = 0; m < N; m++) 
    out2[m] *= expv[m];
  fft(out2, bits, +1);
  for (m = 0; m <= N/2; m++)
    out2[m] *= expk[m] / N;
  for (m = N/2+1; m < N; m++) 
    out2[m] *= expk[abs(m-N)] / N;

  err = 0.0;
  for (m = 0; m < N; m++)
    err += cabs( conj(out[m]) * out2[m] );
    
  free(out2);
  free(expk);
  free(expv);
  return (1.0 - err);
}

int splitstep_solve(complex double *y, size_t bits, double t1, double t2, 
		    double eps, double dtmin, 
		    double (*f)(double, double), double kc, double kappa)
{
  size_t m, N;
  double t, dt, err;
  complex double *ytmp;
  int min_cnt;

  dt = t2 - t1;
  assert((dtmin >= 0.0) && (dt >= dtmin));
  N = (1 << bits);
  ytmp = malloc(N * sizeof(complex double));
  t = t1;
  min_cnt = 0; 
  
  do {
    for(;;) {
      dt = ((t+dt) > t2) ? t2-t : dt;
      err = splitstep(y, t, bits, dt, ytmp, f, kc, kappa);
      err /= eps;
      if (err > 1.0) {
        dt *= SAFETY_FACTOR * pow(err, -0.333333);
        if (dt < dtmin) {
          min_cnt++;
          dt = dtmin;
        }
      } else {
        t += dt;
        dt *= SAFETY_FACTOR * pow(err, -0.333333);
        for (m = 0; m < N; m++) 
          y[m] = ytmp[m];
        break;
      }
    }
  } while ((t2-t) > DBL_MIN);
  free(ytmp);
  return min_cnt;
}
