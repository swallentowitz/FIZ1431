/* rn_parkmiller.c 
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/


#define RND_M 2147483647LL
#define RND_A 16807LL		
#define RND_CONVERSION (1.0/RND_M) 

/*! Calculates random numbers with an multiplicative
    congruential algorithm using the parameters 
    following Park & Miller. 'irnd' is a pointer 
    to the seed (inicial) value, that will be changed 
    and used during the calculation. */
double rand_parkmiller(long long int* irnd)
{
  (*irnd) = (RND_A * (*irnd)) % RND_M;
  return RND_CONVERSION * (*irnd);
}
