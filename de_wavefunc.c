/* de_wavefunc.c
      
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 500 
#include <math.h>
#include <complex.h>
#include <stdlib.h>
#define LN_SQRT_PI (0.5 * log(M_PI))

/*! Calculates the wavefunction at (dimensionless) position 
    'x' for the state being encoded by harmonic-oscillator 
    coeficients 'psi'. */
complex double wavefunction(double x, complex double* psi, size_t sz)
{
  complex double y_old, y, y_new;
  size_t n = sz;
  
  y_old = CMPLX(0.0, 0.0);
  y = CMPLX(0.0, 0.0);
  do {
    y_new = x * sqrt(2.0 / sz) * y - sqrt(1.0-1.0/(sz+1.0)) * y_old 
      + psi[--n];
    y_old = y; 
    y = y_new;
  } while (n > 0);
  return y * exp(-0.5 * (x * x + LN_SQRT_PI));
}

