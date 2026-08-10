/* sf_fac2.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>

double fac(double n)
{
  double nfac;

  if (n <= 1.0)	
    nfac = 1.0;
  else {
    nfac = n;
    do {  
      n -= 1.0;
      nfac *= n;
    } while (n > 1.0);
  }
  return nfac;
}

int main(void)
{
  int n;
  double m;

  for (n = 0; n <= 180; n++) {
    /* Here: automatic type cast */
    m = fac(n);
    printf("fac(%d) = %g\n", n, m);
  }
  return 0;
}
