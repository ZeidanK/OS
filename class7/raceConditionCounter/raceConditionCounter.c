#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NUM_INCREMENTS 10000

void random_sleep();

int counter = 0;

void *increment(void *arg) {
  for (int i = 0; i < NUM_INCREMENTS; i++) {

    counter++; // Race condition here
  }
  return NULL;
}

int main() {
  pthread_t t1, t2;

  pthread_create(&t1, NULL, increment, NULL);
  pthread_create(&t2, NULL, increment, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("Expected counter: %d\n", 2 * NUM_INCREMENTS);
  printf("Actual counter:   %d\n", counter);

  return 0;
}
void random_sleep() {
  int d = (rand() ^ pthread_self() ^ getpid()) % 40 + 40;
  const struct timespec ts = {0, d * 1000 * 1000 * 10};
  nanosleep(&ts, NULL);
}
