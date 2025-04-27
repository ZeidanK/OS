#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAWS 3
#define COLS 5
#define RANGE_UP 20

int mat[RAWS][COLS];
int transposed[COLS][RAWS];

void init_matrix(int matrix[RAWS][COLS]);
void print_matrix(int matrix[RAWS][COLS]);
void *transpose_row(void *arg);

// Initialize the matrix with random numbers
void init_matrix(int matrix[RAWS][COLS]) {
  srand((unsigned int)time(NULL));
  for (int i = 0; i < RAWS; i++) {
    for (int j = 0; j < COLS; j++) {
      matrix[i][j] = rand() % RANGE_UP + 1;
    }
  }
}

// Print the matrix
void print_matrix(int matrix[RAWS][COLS]) {
  for (int i = 0; i < RAWS; i++) {
    for (int j = 0; j < COLS; j++) {
      printf("%4d", matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {
  pthread_t threads[RAWS];

  // Initialize the matrix
  init_matrix(mat);
  printf("Original Matrix:\n");
  print_matrix(mat);

  // TODO
  //  Create threads to transpose rows
  //  each thread will transpose a row into a column
  //  this is how each thread creation will look like -
  //  pthread_create(&threads[i], NULL, transpose_row, (void*)&args[i]);
  for (int i = 0; i < RAWS; i++) {
    pthread_create(&threads[i], NULL, transpose_row, (void *)(long)i);
  }
  for (int i = 0; i < RAWS; i++) {
    pthread_join(threads[i], NULL);
    printf("waiting for thread %d\n", i);
  }
  for (int i = 0; i < RAWS; i++) {
    printf("Thread %d finished\n", i);
  }
  // TODO
  //  Wait for all ahreads to complete

  // Print the transposed matrix
  printf("Transposed Matrix:\n");
  for (int i = 0; i < COLS; i++) {
    for (int j = 0; j < RAWS; j++) {
      printf("%4d", transposed[i][j]);
    }
    printf("\n");
  }

  // TODO
  // print the transposed matrix
  //  you CANNOT use the print_matrix function to print the transposed matrix
  //  (why??) do your own 2 nested loops for the printing

  pthread_exit(NULL);
}

// Thread function to transpose a row into a column
void *transpose_row(void *arg) {
  long row;
  row = (long)arg;
  for (int i = 0; i < COLS; i++) {
    transposed[i][row] = mat[row][i];
  }
  // TODO
  // transpose the row into a column
  // (https://he.wikipedia.org/wiki/%D7%A9%D7%97%D7%9C%D7%95%D7%A3_(%D7%9E%D7%AA%D7%9E%D7%98%D7%99%D7%A7%D7%94))
  //  remember you should transpose a single row into a single column

  pthread_exit(NULL);
}
