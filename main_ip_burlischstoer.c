/* de_solve.c 
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>
#define GAMMA 0.1
#define X0 0.0
#define N 21
#define XMAX 1.0
#define DX (2.0*XMAX/(N-1.0))

double function(double x)
{
  return 1.0 / ((x-X0)*(x-X0) + GAMMA*GAMMA);
}

double ip_neville(double, double*, double*, int);
double ip_burlischstoer(double, double*, double*, int);

int main(void)
{
  int n;
  double xi, yp, yr, ycorrect;
  double x[N], y[N];
  
  for (n = 0; n < N; n++) {
    x[n] = n * DX - XMAX;
    y[n] = function(x[n]);
    printf("%g %g\n", x[n], y[n]);
  }
  printf("\n\n");
  for (xi = -XMAX; xi <= XMAX; xi += 0.005) {
    yp = ip_neville(xi, x, y, N);
    yr = ip_burlischstoer(xi, x, y, N);
    ycorrect = function(xi); 
    printf("%g %g %g %g\n", xi, ycorrect, yp, yr);
  }
  printf("\n\n");
  x[0] = 0.0; y[0] = 1.5;
  x[1] = 1.0; y[1] = 2.3;
  x[2] = 2.0; y[2] = 0.8;
  x[3] = 3.0; y[3] = 1.8;
  x[4] = 4.0; y[4] = 2.0;
  x[5] = 5.0; y[5] = 2.1;
  for (n = 0; n < 6; n++) {
    printf("%g %g\n", x[n], y[n]);
  }
  printf("\n\n");
  for (n = 2; n <= 6; n++) {
    for (xi = x[0]; xi <= x[n-1]; xi += 0.005) {
      yr = ip_burlischstoer(xi, x, y, n);
      printf("%g %g\n", xi, yr);
    } 
    printf("\n\n");
  }
  return 0;
}
