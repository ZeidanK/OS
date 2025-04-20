#include <pthread.h>/* pthread functions and data structures */
#include <stdio.h>  /* standard I/O routines  */

#define NUM_THREADS 5

/* function to be executed by the new thread */
void *printHello(void *threadID) {
  long tid;
  tid = (long)threadID;
  printf("Hello from Thread #%ld!\n", tid);
  printf("Thread id: %ld\n", pthread_self());

  pthread_exit(NULL);
}
/* like any C program, program's execution begins in main */
int main() {
  pthread_t threads[NUM_THREADS]; /* array of thread's ID (just an integer) */
  int rc;                         /* return value */
  long t;                         /* data passed to the new thread */

  /* create a new threads that will execute 'printHello' */
  for (t = 0; t < NUM_THREADS; t++) {
    printf("Creating thread #%ld\n", t);
    rc = pthread_create(&threads[t], NULL, printHello, (void *)t);
    if (rc) /* could not create thread */
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      pthread_exit(NULL); /* terminate the thread */
    }
  }
  // the main waits for all threads to finish and prints a message
  for (t = 0; t < NUM_THREADS; t++) {
    printf("Waiting for thread #%ld to finish...\n", t);
    rc = pthread_join(threads[t], NULL); /* wait for the thread to finish */
    if (rc)                              /* could not join thread */
    {
      printf("ERROR; return code from pthread_join() is %d\n", rc);
      pthread_exit(NULL); /* terminate the thread */
    }
    printf("Thread #%ld has finished!\n", t);
  }

  printf("All threads terminated! Going to exit.\n");

  pthread_exit(NULL);
}
