/*! intro_sum2.c */

#include <stdio.h>

int main (void)
{
  float x;

  /* First small then large stuff. */
  x = 5.0e-8;
  x += 5.0e-8;
  x += 5.0e-8;
  x += 5.0e-8;
  x += 1.0;

  printf("x = %10.8f\n", x);
  return 0;
}
