/* ch_coefint.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/


/* Calculates Chebyshev coeficients 'cint[]' for the 
    integral of a function described by 'c[]'. */
void chebyshev_coefint(double* cint, double* c, double a, 
                       double b, int n)
{
  int j;
  double factor, sum, sgn;
  
  factor = 0.25 * (b-a);
  sum = 0.0;
  sgn = 1.0;
  for (j = 1; j < n-1; j++) {
    cint[j] = factor * (c[j-1] - c[j+1]) / j; 
    sum += sgn * cint[j]; 
    sgn = -sgn;
  }
  cint[n-1]= factor * c[n-2] / (n-1);
  sum += sgn * cint[n-1];
  cint[0] = 2.0 * sum; /* integral at x=a is zero */
}
