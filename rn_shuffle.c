/* rn_shuffle.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#define RND_M 2147483647LL
#define RND_A 16807LL		
#define RND_CONVERSION (1.0/RND_M) 
#define RND_NTAB 32	
#define RND_NDIV (1+(RND_M-1)/RND_NTAB)

/* Calculates a shuffled version of Park-Miller random numbers. */
double rand_shuffle(long long int* irnd)
{
  static long long int iy;
  static long long int iv[RND_NTAB]; 
  static int init = 1;
  int j;

  if (init) {
    for (j = RND_NTAB+7; j >= 0; j--) {
      (*irnd) = (RND_A * (*irnd)) % RND_M;
      if (j < RND_NTAB) 
        iv[j] = (*irnd);
    }
    iy = iv[0];
    init = 0;
  }

  (*irnd) = (RND_A * (*irnd)) % RND_M;  
  j = iy / RND_NDIV;
  iy = iv[j];
  iv[j] = (*irnd);

  return RND_CONVERSION * iy;
}
