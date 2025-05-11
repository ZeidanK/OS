#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define T 8
#define N 2
int counter = 0;
void *foo(void *arg) {
  for (int i = 0; i < N; i++)
    ++counter;
  return NULL;
}
void *bar(void *arg) {
  while (counter < T * N * T)
    ++counter;
  return NULL;
}
int main(int argc, char **argv) {
  pthread_t threads[T];
  if (strcmp(argv[1], "foo") == 0) {
    for (int i = 0; i < T; ++i) {
      pthread_create(&threads[i], NULL, foo, NULL);
    }
  } else {
    for (int i = 0; i < T; ++i) {
      pthread_create(&threads[i], NULL, bar, NULL);
    }
  }
  for (int i = 0; i < T; ++i)
    pthread_join(threads[i], NULL);
  printf("counter = %d\n", counter);
}
