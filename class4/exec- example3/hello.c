#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>


//-----------------------------------------------
int main(int argc, char* argv[])
{
  printf("program: %s, pid = %d\nHello!!\n", argv[0], getpid());
  return 0;
}


