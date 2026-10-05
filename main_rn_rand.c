#include <stdio.h>
#include <stdlib.h>

double rand_parkmiller(long long int*);
double rand_shuffle(long long int*);

int main(void)
{
  long long int irnd1, irnd2;
	int k;
  double res1, res2;
	
	irnd1 = 1;
	irnd2 = 1;
  for (k = 0; k < 100; k++) {
		res1 = rand_parkmiller(&irnd1);
		res2 = rand_shuffle(&irnd2);
		printf("%d %f %f\n", k, res1, res2);    
  }
  return 0;
}
