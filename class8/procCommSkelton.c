#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFSIZE 100

void reverse(char *str1) {
  int i, len, temp;
  len = strlen(str1);

  for (i = 0; i < len / 2; i++) {
    // TODO : reverse the string
    char temp = str1[i];
    str1[i] = str1[len - i - 1];
    str1[len - i - 1] = temp;
  }
}

int main() {
  // Declare two pipe arrays
  int parent_pipe[2], child_pipe[2];

  // Input str
  char str[BUFFSIZE];

  // Declare a buffer to store the received message
  char parent_buff[BUFFSIZE];
  char child_buff[BUFFSIZE];

  // Create the first pipe
  if (pipe(parent_pipe) == -1) {
    perror("cannot create pipe 1");
    exit(1);
  }

  // Create the second pipe
  if (pipe(child_pipe) == -1) {
    perror("cannot create pipe 2");
    exit(1);
  }

  // Fork a child process
  int p;
  p = fork();

  // If the fork failed
  if (p < 0) {
    perror("child fail");
    exit(1);
  }

  if (p == 0) { // If this is the child process
    while (1) {

      // Read a message from the parent_pipe
      ssize_t read_result = read(parent_pipe[0], child_buff, BUFFSIZE);
      // Reverse the string
      printf("the ssize_t is %ld\n", read_result);
      reverse(child_buff);
      // Write the message to the child_pipe
      write(child_pipe[1], child_buff, read_result);
    }
  }
  // If this is the parent process
  else {
    while (1) {
      printf("enter a string:\n");
      scanf("%s", str);
      // Write the message str to the parent_pipe
      write(parent_pipe[1], str, strlen(str) + 1);
      // Read a message from the child_pipe
      read(child_pipe[0], parent_buff, BUFFSIZE);
      // Print the received message
      printf("%s \n", parent_buff);
    }
  }

  return 0;
}
