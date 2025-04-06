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

// **** prog2.c **** 
// Demonstrate that we don't need to fork() first, before we exec().
// What is going to be the output of this program?

//-----------------------------------------------
int main()
{
  char prog_name[20] = "hello";
  char* my_argv[2];
  my_argv[0] = "hello";
  my_argv[1] = NULL;
  
  printf("program pid = %d --> Going to run execv() ...\n", getpid());

  int ret_val = execv(prog_name, my_argv);

  if (ret_val < 0) // does it make sense al all ??
  {
    fprintf(stderr, "*** ERROR: *** EXEC of %s FAILED\n", prog_name);
    exit(1);
  } 
  return 1;
}


