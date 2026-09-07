/* ip_searchidx.c 
      
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/
   
#include <assert.h>

/* Search index j with \f$x[j] <= x < x[j+1]\f$ in the monotonically-increasing
   ordered list \f$x[i+1] >= x[i]\f$. Done by  the method of bisection. */
int searchidx(double xi, double* x, int n)

{
  int lo, hi, mid;
  
  assert((xi >= x[0]) && (xi <= x[n-1]));
  
  lo = 0; 
  hi = n-1;
  do {
    mid = (lo+hi)/2;
    if (xi < x[mid])
      hi = mid;
    else
      lo = mid;
  } while (hi-lo > 1);
  return lo;
}
