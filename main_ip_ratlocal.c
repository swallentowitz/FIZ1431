/* main_ip_ratlocal.c 
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>
#define GAMMA 0.1
#define X0 0.1
#define N 41
#define XMAX 0.5
#define DX (2.0*XMAX/(N-1.0))

double function(double x)
{
  double res;
  res = 0.0008 / (x*x + 0.001* GAMMA*GAMMA);
  res += 1.0 / ((x-X0)*(x-X0) + GAMMA*GAMMA);
  return res;
}

double ip_polylocal(double, int, double*, double*, int);
double ip_burlischstoer(double, double*, double*, int);
double ip_ratlocal(double, int, double*, double*, int);

int main(void)
{
  int n;
  double xi, yi, ycorrect;
  double x[N], y[N];
  double yi4, yi5, yi6;
  double yp4, yp5, yp6;
  
  for (n = 0; n < N; n++) {
    x[n] = n * DX - XMAX;
    y[n] = function(x[n]);
    printf("%g %g\n", x[n], y[n]);
  }
  printf("\n\n");
  for (xi = -XMAX; xi <= XMAX; xi += 0.005) {
    yi = ip_burlischstoer(xi, x, y, N);
    yi4 = ip_ratlocal(xi, 4, x, y, N);
    yi5 = ip_ratlocal(xi, 5, x, y, N);
    yi6 = ip_ratlocal(xi, 6, x, y, N);
    yp4 = ip_polylocal(xi, 4, x, y, N);
    yp5 = ip_polylocal(xi, 5, x, y, N);
    yp6 = ip_polylocal(xi, 6, x, y, N);
    ycorrect = function(xi); 
    printf("%g %g %g %g %g %g %g %g %g\n", 
           xi, ycorrect, yi, yi4, yi5, yi6, 
           yp4, yp5, yp6);
  }
  return 0;
}
