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
  printf("**** Hello %s !!! ****\n", argv[1]);
  return 0;
}


