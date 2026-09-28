/* main_ft_fft.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 500
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#define bits 8
#define N 256
#define XMAX 2.0
#define DX XMAX/N
#define VC 0.5/DX

void fft(complex double*, size_t, int);

double a, b;

complex double function(double x)
{
  return exp(-a * x * x) + b * (rand()/((double)RAND_MAX)-0.5);
}

double xvalue(size_t n)
{
  return XMAX * (n - 0.5 * N) / N;
}

double freqvalue(int n)
{
  return n * 2.0 * VC / N; 
}

complex double factor(int n)
{ 
  return exp(-M_PI * I * freqvalue(n) * XMAX);
}  

int main(void)
{
  complex double data[N];
  size_t n;
  double x;
  complex double res;
  
  a = 100.0;
  b = 0.0;
  for (n = 0; n < N; n++) {
    x = xvalue(n);
    data[n] = function(x);
    printf("%f %f %f\n", x, creal(data[n]), cimag(data[n]));
  }
  printf("\n\n");

  fft(data, bits, 1);
  for (n = N/2+1; n < N; n++) {
    res = data[n] * factor(n-N);
    printf("%f %f %f\n", freqvalue(n-N), creal(res), cimag(res));
  }
  for (n = 0; n <= N/2; n++) {
    res = data[n] * factor(n);
    printf("%f %f %f\n", freqvalue(n), creal(res), cimag(res));
  }
  printf("\n\n");

  fft(data, bits, -1);
  for (n = 0; n < N; n++) {
    x = xvalue(n);
    printf("%f %f %f\n", x, creal(data[n])/N, cimag(data[n])/N);
  }
  printf("\n\n");
  
  a = 100.0;
  b = 0.2;
  for (n = 0; n < N; n++) {
    x = xvalue(n);
    data[n] = function(x);
    printf("%f %f %f\n", x, creal(data[n]), cimag(data[n]));
  }
  printf("\n\n");

  fft(data, bits, 1);
  for (n = N/2+1; n < N; n++) {
    res = data[n] * factor(n-N);
    printf("%f %f %f\n", freqvalue(n-N), creal(res), cimag(res));
  }
  for (n = 0; n <= N/2; n++) {
    res = data[n] * factor(n);
    printf("%f %f %f\n", freqvalue(n), creal(res), cimag(res));
  }
  printf("\n\n");

  fft(data, bits, -1);
  for (n = 0; n < N; n++) {
    x = xvalue(n);
    printf("%f %f %f\n", x, creal(data[n])/N, cimag(data[n])/N);
  }
  return 0;
}
