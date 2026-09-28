/* ft_fft.c
     
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define _XOPEN_SOURCE 500 
#include <math.h>
#include <stdlib.h>
#include <complex.h>

size_t bit_reverse(size_t, size_t);

/* Calculates the Fourier (inverse if 'isign=-1') sum 
   of 2^'bits' 'data' and saves result in 'data'. */
void fft(complex double *data, size_t bits, int isign)
{
  complex double tmp, w, z;
  double wtmp, delta;
  size_t blocks, points, lines;
  size_t b, l, k;
  size_t lo, hi;

  /* Bit-reversal of the data: */
  points = (1 << bits);	
  for (k = 0; k < points; k++) {
    b = bit_reverse(k, bits);
    if (b > k) {
      tmp = data[k];
      data[k] = data[b];
      data[b] = tmp;
    }
  }

  blocks = (points >> 1); /* blocks=points/2 */
  points = 2;  
  lines = 1;   		
  for (k = 0; k < bits; k++) { 
    lo = 0; 

    /* start recurrence for trigonometrics */
    delta = isign * 2.0 * M_PI / points;
    wtmp = sin(0.5 * delta);
    z = 2.0 * wtmp * wtmp - I * sin(delta);

    for (b = 0; b < blocks; b++) { 
      w = 1.0;
      hi = lo + lines; 
      for (l = 0; l < lines; l++) { 
        tmp = w * data[hi+l];
        data[hi+l] = data[lo+l] - tmp;
        data[lo+l] += tmp;
        w -= (z * w);
      }
      lo += points; 
    }
    blocks >>= 1;
    lines <<= 1;
    points <<= 1;
  }
}

