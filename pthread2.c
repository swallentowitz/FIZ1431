/* pthread2.c
   
   Copyright (c) 2026 Sascha Wallentowitz
   
   Permission is granted under the MIT License.
   See the LICENSE file for details.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* WINDOWS: <windows.h> */

int counter = 0;
pthread_mutex_t lock;

void* task(void* arg)
{
  int id, n;
  
  id = *(int*)arg;

  for (n = 0; n < 10; n++) {
    sleep((int)(10 * ((double)rand()) / RAND_MAX)); /* Sleep for 20 seconds */
  
    pthread_mutex_lock(&lock);
    counter++; // Protected critical section
    printf("Id = %d, counter = %d\n", id, counter);
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

int main()
{
  pthread_t thread1, thread2;
  int id1, id2;

  id1 = 1;
  id2 = 2;
  
  pthread_mutex_init(&lock, NULL);
  
  pthread_create(&thread1, NULL, task, &id1);
  pthread_create(&thread2, NULL, task, &id2);
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  
  pthread_mutex_destroy(&lock);
  return 0;
}
