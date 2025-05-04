#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2
#define MAX_COUNT 1000000

int counter = 0;
sem_t semaphore; // Semaphore to control access to counter

void *increment_counter(void *arg) {
  int i;
  for (i = 0; i < MAX_COUNT; i++) {
    // Wait for the semaphore (decrement its value)
    sem_wait(&semaphore);

    // Critical section: Increment the counter
    counter++;

    // Signal the semaphore (increment its value)
    sem_post(&semaphore);
  }

  pthread_exit(NULL);
}

int main(void) {
  pthread_t threads[NUM_THREADS];
  int i;

  // Initialize the semaphore with an initial value of 1
  // (1 resource available) if we init it with 2 rathar than 1 then nothing
  // really changes as two can enter at the same time in that case
  if (sem_init(&semaphore, 0, 1) != 0) {
    perror("Semaphore initialization failed");
    return 1;
  }

  // Create the threads
  for (i = 0; i < NUM_THREADS; i++) {
    if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
      perror("Thread creation failed");
      return 1;
    }
  }

  // Wait for the threads to finish
  for (i = 0; i < NUM_THREADS; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("Thread join failed");
      return 1;
    }
  }

  // Print the final value of the counter
  printf("Final counter value: %d\n", counter);

  // Destroy the semaphore
  sem_destroy(&semaphore);

  return 0;
}
