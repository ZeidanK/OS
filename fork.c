#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

  pid_t pid;
  pid = fork();
  if (pid == 0) {
    printf("id: %d Child process\n", getpid());
    printf("id without the function getpid(): %d\n", pid);
    pid = fork();
    if (pid == 0) {
      printf("id: %d Child process\n", getpid());
      printf("id without the function getpid(): %d\n", pid);

    } else {
      wait(NULL);
      printf("id: %d Child process is done\n", getpid());
      printf("id without the function getpid(): %d\n", pid);
    }
  } else {
    printf("id: %d Parent process\n", getpid());
    printf("id without the function getpid(): %d\n", pid);
    wait(NULL);
    printf("id: %d Child process is done\n", getpid());
  }
  printf("all process is done\n");
  return 0;
}
