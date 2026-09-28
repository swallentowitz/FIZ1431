/* ft_bitrev.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/
   
#include <stdlib.h>

/*! Returns 'n' with 'bits' numbers of bits bit-reversed. */
size_t bit_reverse(size_t n, size_t bits)
{
  size_t m, nrev;

  nrev = 0;
  m = 0;
  do {
    nrev <<= 1;       /* shift bits of nrev to left */
    nrev += (n % 2);  /* lowest bit of n -> highest bit of nrev */
    n >>= 1;          /* shift bits of n to right */
    m++;              /* we did one more bit */
  } while (m < bits);

  return nrev;
}
    
  
