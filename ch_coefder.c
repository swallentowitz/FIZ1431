/* ch_coefder.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/


/* Calculates the coeficients 'cder[]' for the derivative
    of the function corresponding to 'c[]'. */
void chder(double* cder, double* c, double a, double b, int n)
{
  int j;
  double factor;
  
  factor = 4.0 / (b - a);
  cder[n-1] = 0.0; 
  cder[n-2] = factor * (n - 1.0) * c[n-1];
  for (j = n-3; j >= 0; j--)
    cder[j] = cder[j+2] + factor * (j + 1.0) * c[j+1]; 
}
