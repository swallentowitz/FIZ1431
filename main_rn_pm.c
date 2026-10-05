/* main_rn_pm.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>
#include <stdlib.h>
#define NBIN 50
#define N 40000000L
#define P (2.0/N)

double rand_parkmiller(long long int*);
int searchidx(double, double*, int);

int main(void)
{
  long long int irnd;
  long int n;
  int xpos, ypos;
  double x, y;
  double bin[NBIN][NBIN];
  double binscale[NBIN+1];

  for (xpos = 0; xpos <= NBIN; xpos++) 
    binscale[xpos] = xpos / ((double)NBIN);
  for (xpos = 0; xpos < NBIN; xpos++)
    for (ypos = 0; ypos < NBIN; ypos++)
      bin[xpos][ypos] = 0.0;

  irnd = 1;
  for (n = 0; n < N; n++) {
    x = rand_parkmiller(&irnd);
    y = rand_parkmiller(&irnd);
    xpos = searchidx(x, binscale, NBIN+1);
    ypos = searchidx(y, binscale, NBIN+1);
    bin[xpos][ypos] += P;
  }
    
  for (xpos = 0; xpos < NBIN; xpos++) { 
    for (ypos = 0; ypos < NBIN; ypos++)
      printf("%f %f %f\n", binscale[xpos], binscale[ypos], 
             bin[xpos][ypos]);
    printf("\n");
  }
  
  printf("\n\n\n");
  
  for (xpos = 0; xpos < NBIN; xpos++)
    for (ypos = 0; ypos < NBIN; ypos++)
      bin[xpos][ypos] = 0.0;
  
  srand(1);
  for (n = 0; n < N; n++) {
    x = rand() / ((double)RAND_MAX);
    y = rand() / ((double)RAND_MAX);
    xpos = searchidx(x, binscale, NBIN+1);
    ypos = searchidx(y, binscale, NBIN+1);
    bin[xpos][ypos] += P;
  }
    
  for (xpos = 0; xpos < NBIN; xpos++) { 
    for (ypos = 0; ypos < NBIN; ypos++)
      printf("%f %f %f\n", binscale[xpos], binscale[ypos], 
             bin[xpos][ypos]);
    printf("\n");
  }

  return 0;
}
