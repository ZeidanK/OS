#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void *print_msg(void *ptr);
void random_sleep();

//----------------------------------------
int main() {
  pthread_t thread1, thread2;
  char *msg_main = "Main Thread";
  char *msg1 = "Thread #1";
  char *msg2 = "Thread #2";

  /* Create independent threads. each one runs the print_msg. */

  pthread_create(&thread1, NULL, print_msg, (void *)msg1);
  pthread_create(&thread2, NULL, print_msg, (void *)msg2);
  print_msg(msg_main);
  // the following lines are not executed. WHY?
  printf("This message should not be printed!\n");
  // wait(NULL); wait(NULL);  // is this right?
  exit(0);
}

//----------------------------------------
void *print_msg(void *ptr) {
  char *msg;
  msg = (char *)ptr;
  random_sleep();
  printf("%s \n", msg);
  pthread_exit(NULL);
}

//----------------------------------------
void random_sleep() {
  int d = (rand() ^ pthread_self() ^ getpid()) % 40 + 40;
  const struct timespec ts = {0, d * 1000 * 1000 * 10};
  nanosleep(&ts, NULL);
}
