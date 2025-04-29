#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_ITERATIONS 5

// Shared variables for Peterson's Algorithm
bool flag[2] = {false, false};
int turn = 0;

// Shared resource
int shared_counter = 0;

// Thread function for process 0
void *process0(void *arg) {
  for (int i = 0; i < NUM_ITERATIONS; i++) {
    // Entry section
    flag[0] = true;
    turn = 1;
    while (flag[1] && turn == 1) {
      // Busy wait
    }

    // Critical section
    printf("Process 0 entering critical section.\n");
    shared_counter++;
    printf("Process 0 exiting critical section. Counter: %d\n", shared_counter);

    // Exit section
    flag[0] = false;

    // Remainder section
    sleep(1); // Simulate some work outside the critical section
  }
  return NULL;
}

// Thread function for process 1
void *process1(void *arg) {
  for (int i = 0; i < NUM_ITERATIONS; i++) {
    // Entry section
    flag[1] = true;
    turn = 0;
    while (flag[0] && turn == 0) {
      // Busy wait
    }

    // Critical section
    printf("Process 1 entering critical section.\n");
    shared_counter++;
    printf("Process 1 exiting critical section. Counter: %d\n", shared_counter);

    // Exit section
    flag[1] = false;

    // Remainder section
    sleep(1); // Simulate some work outside the critical section
  }
  return NULL;
}

int main() {
  pthread_t t0, t1;

  // Create threads for process 0 and process 1
  pthread_create(&t0, NULL, process0, NULL);
  pthread_create(&t1, NULL, process1, NULL);

  // Wait for threads to finish
  pthread_join(t0, NULL);
  pthread_join(t1, NULL);

  printf("Final counter value: %d\n", shared_counter);
  return 0;
}
