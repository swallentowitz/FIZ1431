/* ch_approx.c 
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <assert.h>

/*! Calculates the Chebyshev approximation at the value 'x' 
    within the interval ['a','b'] using 'm' of the Chebyshev 
    coeficients 'c[]'. */ 
double chebyshev_approx(double x, double a, double b, 
                        double* c, int m)
{
  double alpha, h_new, h, h_old;
  int n;
  
  assert((a <= x) && (x <= b));  
  alpha = 2.0 * (2.0 * x - (a + b)) / (b - a);  
  h_old = 0.0; h = 0.0;
  for (n = m-1; n >= 0; n--) {
    h_new = alpha * h - h_old + c[n];
    h_old = h;
    h = h_new;
  }
  return h - 0.5 *( alpha * h_old + c[0]);
}
