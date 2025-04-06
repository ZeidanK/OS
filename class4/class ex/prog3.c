#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <string.h>

// **** prog3.c **** 
// Demonstrate how to work with command line arguments

char* my_argv[2];

//-----------------------------------------------
int main(int argc, char* argv[])
{
  
  // complete the following two lines: 
  char prog_name[20] = "????";
  my_argv[0] = "????";
  my_argv[1] = "????";
  my_argv[2] = NULL;


  execve(prog_name, my_argv, NULL);
  fprintf(stderr, "*** ERROR: *** EXEC of %s FAILED\n", prog_name);
  exit(1);
}


