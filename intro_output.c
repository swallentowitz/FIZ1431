/* intro_output.c 
  
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
  double dx, x, y;
  int n, nmax;
    
  nmax = 10;
  dx = 2.0 * M_PI / nmax;

  x = 0.0;
  for (n = 0; n < nmax; n++)
  {
    x += dx;
    y = sin(x);
    printf("%e %e\n", x, y);
  }
  return 0;
}
