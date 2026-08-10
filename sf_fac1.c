/* sf_fac1.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <stdio.h>

int fac(int n)
{
  int nfac;

  if (n <= 1)	
    nfac = 1;
  else {
    nfac = n;
    do {
      n = n - 1;
      nfac = nfac * n;
    } while (n > 1);
  }
  return nfac;
}

int main(void)
{
  int n, m;

  for (n = 0; n <= 40; n = n + 1) {
    m = fac(n);
    printf("fac(%d) = %d\n", n, m);
  }
  return 0;
}
