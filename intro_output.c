/* intro_output.c */
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
