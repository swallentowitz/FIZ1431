/* main_rn_shuffle.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>
#define NBIN 300
#define N 400000000L
#define P (2.0/N)

double rand_parkmiller(long long int*);
double rand_shuffle(long long int*);
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
  
  irnd = 1;
  for (n = 0; n < N; n++) {
    x = rand_shuffle(&irnd);
    y = rand_shuffle(&irnd);
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
