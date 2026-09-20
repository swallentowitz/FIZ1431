/* main_ig_romberg.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <math.h>
#include <stdio.h>
#include <float.h>
/* Laser resonator: */                
#define R_S      0.05       /* reflection of mirrors */
#define T_S      (1.0-R_S)  /* transmission of mirrors */
#define OMEGA_0  1.0        /* resonance frequency */
#define GAMMA    0.5        /* natural linewidth */
#define KAPPA_0 -0.10       /* absorption at OMEGA_0 */
#define L        29.0       /* effective length */

int count;

double ig_simpsonext(double (*f)(double), double, double, double);
double ig_romberg(double (*f)(double), double, double, int, double);
double ig_romberg_simpsonext(double (*f)(double), double, double, int, double);

double power(double omega)
{
    double f, kappa, intensity;
    
    count++;
    kappa = KAPPA_0 * GAMMA * GAMMA 
      / ((omega-OMEGA_0)*(omega-OMEGA_0) + GAMMA*GAMMA);
    f = R_S * R_S * exp(-2.0 * kappa * L);
    intensity = T_S * T_S * T_S * T_S 
      / (1.0 + f*f - 2.0 * f * cos(2.0*omega*L));
    return intensity;
}

int main(void)
{
  double p, eps;
  
  printf("Simpson extended:\n"
	 "eps\t\teff. power\tfunction calls\n");
  for (eps = 1.0e-5; eps >= 1.0e-6; eps *= 0.1) {
    count = 0;  
    p = ig_simpsonext(power, 0.2, 2.0, eps);
    printf("%e\t%13.12f\t%d\n", eps, p, count);
  }
  
  printf("Romberg extended trapezoidal:\n"
	 "eps\t\teff. power\tfunction calls\n");
  for (eps = 1.0e-5; eps >= 1.0e-10; eps *= 0.1) {
    count = 0;  
    p = ig_romberg(power, 0.2, 2.0, 5, eps);
    printf("%e\t%13.12f\t%d\n", eps, p, count);
  }
  
  printf("Romberg Simpson extended:\n"
	 "eps\t\teff. power\tfunction calls\n");
  for (eps = 1.0e-5; eps >= 1.0e-10; eps *= 0.1) {
    count = 0;  
    p = ig_romberg_simpsonext(power, 0.2, 2.0, 5, eps);
    printf("%e\t%13.12f\t%d\n", eps, p, count);
  }
    
  return 0;
}
