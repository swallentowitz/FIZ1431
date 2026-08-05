/* intro_sum2.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>

int main (void)
{
  float x;

  x = 5.0e-8;
  x += 5.0e-8;
  x += 5.0e-8;
  x += 5.0e-8;
  x += 1.0;

  printf("x = %10.8f\n", x);
  return 0;
}
