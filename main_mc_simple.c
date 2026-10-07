/* main_mc_simple.c 
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 800
#include <math.h>
#include <stdio.h>
#define ALPHA (0.1 * M_PI)
#define N 1000
#define R 1
#define H 0.1
#define V (H * (2.0 * M_PI - ALPHA) * R * R / 2.0)


double rand_shuffle(long long int*);

int inside(double phi)
{
  return (((phi > ALPHA) && (phi <= 2.0 * M_PI)) ? 1 : 0);
}

int main(void)
{
  long long int irnd;
  double r, phi, r3;
  double avg, var, err;
  int i;

  irnd = 1;
  avg = 0.0;
  var = 0.0;
  for (i = 1; i <= N; i++) {
    r = rand_shuffle(&irnd);
    phi = 2.0 * M_PI * rand_shuffle(&irnd);
    r3 = r * r * r;
    avg += (inside(phi) ? r3 : 0.0);
    var += (inside(phi) ? (r3 * r3) : 0.0);
    err = V * sqrt((var / i - avg * avg / (i*i)) / i);
    printf("%d\t%f\t%f\n", i, avg * V / i, err);
  }
}
