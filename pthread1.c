/* pthread1.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h> /* WINDOWS: <windows.h> */

void* task(void* arg)
{
  int nmax, n;
  double res;
  double dummy[100000];

  sleep(20); /* Sleep for 20 seconds */
  
  nmax = *(int*)arg;
  res = 1.0;
  for (n = 1; n < nmax; n++)
    res *= n;
  printf("Factorial %d! = %f\n", nmax, res);
  return NULL;
}

int main()
{
  pthread_t thread1, thread2;
  int val1, val2;
  
  val1 = 10;
  val2 = 15;
  
  pthread_create(&thread1, NULL, task, &val1);
  pthread_create(&thread2, NULL, task, &val2);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  return 0;
}
