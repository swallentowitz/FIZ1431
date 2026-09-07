/* main_ip_polylocal.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>
#define GAMMA 0.1
#define X0 0.0
#define N 20
#define XMAX 1.0
#define DX (2.0*XMAX/(N-1.0))

double function(double x)
{
  return 1.0 / ((x-X0)*(x-X0) + GAMMA*GAMMA);
}

double ip_neville(double, double*, double*, int);
double ip_polylocal(double, int, double*, double*, int);

int main(void)
{
  int n;
  double xi, yi, yi_local, ycorrect;
  double x[N], y[N];
  
  for (n = 0; n < N; n++) {
    x[n] = n * DX - XMAX;
    y[n] = function(x[n]);
    printf("%g %g\n", x[n], y[n]);
  }
  printf("\n\n");
  for (xi = -XMAX; xi <= XMAX; xi += 0.005) {
    yi = ip_neville(xi, x, y, N);
    yi_local = ip_polylocal(xi, 4, x, y, N);
    ycorrect = function(xi); 
    printf("%g %g %g %g\n", xi, ycorrect, yi, yi_local);
  }
  return 0;
}
