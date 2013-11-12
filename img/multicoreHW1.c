#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_TASKS  5
int inArray[30]={10,15,20,25,30,35,0,10,20,30,40,50,2,12,22,32,42,52,4,14,24,34,44,54,5,15,25,35,45,55};
int threadSum[NUM_TASKS];
void *task(int id) {
  printf("Task %d started\n", id);
  int i;
  int result = 0;
  int start = id*6;
  for (i = 0; i < 6; i++) {
    result = result + inArray[start+i];
  }
  threadSum[id] = result;
  printf("Task %d completed with result %d\n", id, result);
}

void *threaded_task(void *t) {
  long id = (long) t;
  printf("Thread %ld started\n", id);
  task(id);
  printf("Thread %ld done\n", id);
  pthread_exit(0);
}

void *parallel(int num_tasks)
{
  int num_threads = num_tasks;
  pthread_t thread[num_threads];
  int rc;
  long t;
  int sum=0;
  for (t = 0; t < num_threads; t++) {
    printf("Creating thread %ld\n", t);
    rc = pthread_create(&thread[t], NULL, threaded_task, (void *)t);
    if (rc) {
      printf("ERROR: return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
// wait for all the threads to complete 
  for (t=0; t< NUM_TASKS; t++)
      pthread_join(thread[t], NULL);

  for (t=0; t< NUM_TASKS; t++)
      sum = sum + threadSum[t];

  printf("\n Sum:  %d\n", sum);
 }

int main(int argc, char *argv[]) {
  int t;
  parallel(NUM_TASKS);
  pthread_exit(NULL);
  printf("Main completed\n");
  pthread_exit(NULL);
}
