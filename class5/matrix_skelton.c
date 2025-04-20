#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void init_arr(int *);
void print_arr(int *);
void random_sleep();
void *do_thread(void *);

// constants and global variables
#define RAWS 3
#define COLS 5
#define RANGE_UP 20

int mat[RAWS][COLS];

//------------------------------------------------
void init_arr(int *arr) {
  // srand((unsigned int) pthread_self());
  for (int j = 0; j < COLS; j++)
    arr[j] = rand() % RANGE_UP + 1;
}

//------------------------------------------------
void print_arr(int *arr) {
  printf("thread %d: ", (int)pthread_self());
  for (int j = 0; j < COLS; j++)
    printf("%*d", 4, arr[j]);
  printf("\n");
}

//------------------------------------------------
int main() {
  // pthread_t threads[RAWS];
  pthread_t thread[RAWS]; // array of thread's ID (just an integer)
  for (int j = 0; j < RAWS; j++)
    init_arr(mat[j]);
  printf("Done with initialization, going to print the matrix line by line.\n");
  // create a new thread to print each line of the matrix
  for (int j = 0; j < RAWS; j++) {
    // pthread_t thread[j]; // array of thread's ID (just an integer)
    pthread_create(&thread[j], NULL, do_thread, (void *)mat[j]);
    //   printf("waiting for thread %d to finish...\n", (int)thread);
    //   pthread_join(thread[j], NULL); // wait for the thread to finish
    // printf("Thread %d has finished!\n", (int)thread);
  }
  for (int j = 0; j < RAWS; j++) {
    printf("waiting for thread %d to finish...\n", (int)thread[j]);
    pthread_join(thread[j], NULL); // wait for the thread to finish
    printf("Thread %d has finished!\n", (int)thread[j]);
  }
  // for (int j = 0; j < RAWS; j++)
  //   print_arr(mat[j]);

  /*
    // When you modify this code to use threads -
    // wait for threads to complete - complete this code
    for (int j=0; j < RAWS; j++)
    {
      pthread_join(---, NULL);
    }
  */

  printf("thread %d: ALL Threads terminated! Going to exit.\n",
         (int)pthread_self());
  pthread_exit(NULL);
  // exit(0);
}

//------------------------------------------------
void *do_thread(void *ptr) {
  int *mat = (int *)ptr;

  // print_arr(mat);
  init_arr(mat);

  // place holder for init_arr call
  random_sleep();
  // place holder for print_arr call

  print_arr(mat);
  pthread_exit(NULL);
}

//----------------------------------------
void random_sleep() {
  int d = (rand() ^ pthread_self() ^ getpid()) % 40 + 40;
  const struct timespec ts = {0, d * 1000 * 1000 * 10};
  nanosleep(&ts, NULL);
}

// questions 1)->c  2)->c 3)->b (thread is foaster to create)
// //4)-> d  5)->c
