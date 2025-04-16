#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/wait.h>

//-----------------------------------------------
int main(int argc, char* argv[])
{
  printf("**** Hello %s !!! **** , (pid=%d ppid=%d), program: %s\n", argv[1], getpid(), getppid(), argv[0]);
  exit(0); 
}


