/* ft_step.c
     
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 500 
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include <float.h>
#define BITS 8
#define N ((1 << (BITS)))
#define KC 5.0
#define DQ (1.0/(2.0 * (KC)))
#define DK (2.0 * (KC) / (N))
#define KAPPA (-(N)/2)
#define QMAX ((DQ) * (N)/2)
#define SIGMA2 ((N)/10)
#define DT 10
#define TFIN (100 * (DT))
#define EPS 1e-5
#define DTMIN 1e-10

int splitstep_solve(complex double*, size_t, double, double, double, double, 
		    double (*f)(double, double), double, double);


/* potencial tipo caja: */
double potential(double q, double tau)
{
  return (((q > -QMAX) && (q < QMAX)) ? 1.0 : 0.0);
}




int main(void)
{
  size_t m;
  complex double psi[N];
  double t, nrm, tmp;

  /* initial state: Gaussian in momentum */
  nrm = 0.0;
  for (m = 0; m < N/2; m++) {
    psi[m] = exp(-0.5 * (m - 0.25 * N) * (m - 0.25 * N) / SIGMA2);
    tmp = cabs(psi[m]);
    nrm += tmp * tmp;
  }
  for (m = N/2+1; m < N; m++)
    psi[m] = 0.0;
  tmp = 1.0 / sqrt(nrm);
  for (m = 0; m < N/2; m++) 
    psi[m] *= tmp;
 
  for (t = 0.0; t < TFIN; t += DT) {
    nrm = 0.0;
    for (m = N/2+1; m < N; m++) {
      tmp = cabs(psi[m]);
      tmp *= tmp;
      nrm += tmp;
      printf("%ld\t%f\n", (m-N), tmp);
    }
    for (m = 0; m <= N/2; m++) {
      tmp = cabs(psi[m]);
      tmp *= tmp;
      nrm += tmp;
      printf("%ld\t%f\n", m, tmp);
    }
    printf("\n\n");
    if (fabs(nrm - 1.0) > 1.0e-5)
      fprintf(stderr, "Norm = %e\n", nrm);
    splitstep_solve(psi, BITS, t, t + DT, EPS, DTMIN, potential, KC, KAPPA);
  }
  

  return 0;
}
