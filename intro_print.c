/* intro_print.c
  
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/


#include <stdio.h>

int main(void)
{
  float x;
  int i;

  x = 1.542e-3;
  i = 9845;
  printf("Huhu...some stupid output:\n"
         "x = %f = %e\n"
         "i = %d\n", x, x, i);
  return 0;
}
