#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void init_arr(int*);
void print_arr(int *);
void random_sleep();
void* do_thread( void*);

// constants and global variables
#define RAWS 3
#define COLS 5
#define RANGE_UP 20

int mat[RAWS][COLS];

//------------------------------------------------
void init_arr(int* arr)
{
  // srand((unsigned int) pthread_self());
  for (int j=0; j < COLS; j++)
    arr[j] = rand() % RANGE_UP + 1;
}

//------------------------------------------------
void print_arr(int* arr)
{
  printf("thread %d: ", (int) pthread_self());
  for (int j=0; j < COLS; j++)
    printf("%*d", 4, arr[j]);
  printf("\n");
}


//------------------------------------------------
int main()
{
  // pthread_t threads[RAWS];

  for (int j=0; j < RAWS; j++)
    init_arr(mat[j]);
  printf("Done with initialization, going to print the matrix line by line.\n");
  
  for (int j=0; j < RAWS; j++)
    print_arr(mat[j]);
  
/*
  // When you modify this code to use threads - 
  // wait for threads to complete - complete this code
  for (int j=0; j < RAWS; j++)
  {
    pthread_join(---, NULL);
  }
*/
  

  printf("thread %d: ALL Threads terminated! Going to exit.\n", (int) pthread_self());
  pthread_exit(NULL);
  // exit(0);
}

//------------------------------------------------
void* do_thread( void *ptr )
{
  // place holder for init_arr call
  random_sleep();
  // place holder for print_arr call

  pthread_exit(NULL);  
}

//----------------------------------------
void random_sleep()
{
  int d = (rand() ^ pthread_self() ^ getpid()) % 40 + 40;
  const struct timespec ts = {0, d * 1000 * 1000 * 10};
  nanosleep(&ts, NULL);
}

