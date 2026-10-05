/* main_rn_corr.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>
#define M 64

int main(void)
{
  int a, c, r[M], n;
  
  a = 165;
  c = 87;
  
  r[0] = 1;
  for (n = 1; n < M; n++) 
    r[n] = (a * r[n-1] + c) % M;
    
  for (n = 0; n < M-1; n += 2) 
    printf("%d %d\n", r[n], r[n+1]);  

  return 0;
}
