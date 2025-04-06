#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// **** prog3.c ****
// Demonstrate how to work with command line arguments

char *my_argv[2];

//-----------------------------------------------
int main(int argc, char *argv[]) {

  // complete the following two lines:
  char prog_name[20] = "hellowho";
  my_argv[0] = prog_name;
  my_argv[1] = argv[1];
  my_argv[2] = NULL;

  execve(prog_name, my_argv, NULL);
  fprintf(stderr, "*** ERROR: *** EXEC of %s FAILED\n", prog_name);
  exit(1);
}
