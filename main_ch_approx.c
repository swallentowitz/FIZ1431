/* main_ch_aprox.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <math.h>
#include <stdio.h>
#define GAMMA 0.1
#define X0 0.1
#define XMAX 0.5

double function1(double x)
{
  double res;
  res = 0.0008 / (x*x + 0.001* GAMMA*GAMMA);
  res += 1.0 / ((x-X0)*(x-X0) + GAMMA*GAMMA);
  return res;
}

double function2(double x)
{
 	double res;
  res = 1.0 / ((x-X0)*(x-X0) + GAMMA*GAMMA);
  return res;
}

void chebyshev_coef(double (*)(double), double, double, double*, int);
double chebyshev_approx(double, double, double, double*, int);
                        
int main(void)
{
  double x, c[200];
  
  for (x = -XMAX; x <= XMAX; x += 0.005) 
    printf("%g %g %g\n", 
           x, function1(x), function2(x));
  printf("\n\n");
	
  chebyshev_coef(function2, -XMAX, XMAX, c, 5);
  for (x = -XMAX; x <= XMAX; x += 0.005) 
    printf("%g %g\n", 
           x, chebyshev_approx(x, -XMAX, XMAX, c, 5));
  printf("\n\n");	
	
  chebyshev_coef(function2, -XMAX, XMAX, c, 10);
  for (x = -XMAX; x <= XMAX; x += 0.005) 
    printf("%g %g\n", 
           x, chebyshev_approx(x, -XMAX, XMAX, c, 10));
  printf("\n\n");					 
	
  chebyshev_coef(function2, -XMAX, XMAX, c, 20);
  for (x = -XMAX; x <= XMAX; x += 0.005) 
    printf("%g %g\n", 
           x, chebyshev_approx(x, -XMAX, XMAX, c, 20));
  printf("\n\n");		
	
  chebyshev_coef(function2, -XMAX, XMAX, c, 20);
  for (x = -XMAX; x <= XMAX; x += 0.005) 
    printf("%g %g\n", 
           x, chebyshev_approx(x, -XMAX, XMAX, c, 10));
  printf("\n\n");
	
  chebyshev_coef(function1, -XMAX, XMAX, c, 100);
  for (x = -XMAX; x <= XMAX; x += 0.005) 
    printf("%g %g\n", 
           x, chebyshev_approx(x, -XMAX, XMAX, c, 100));
  printf("\n\n");	
	
  chebyshev_coef(function1, -XMAX, XMAX, c, 200);
  for (x = -XMAX; x <= XMAX; x += 0.005) 
    printf("%g %g\n", 
           x, chebyshev_approx(x, -XMAX, XMAX, c, 200));
  printf("\n\n");	
           
  return 0;
}
