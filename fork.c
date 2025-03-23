#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

  pid_t pid;
  pid = fork();
  if (pid == 0) {
    printf("id: %d Child process\n", getpid());
    pid = fork();
    if (pid == 0) {
      printf("id: %d Child process\n", getpid());
    } else {
      wait(NULL);
      printf("id: %d Child process is done\n", getpid());
    }
  } else {
    printf("id: %d Parent process\n", getpid());
    wait(NULL);
    printf("id: %d Child process is done\n", getpid());
  }
  printf("all process is done\n");
  return 0;
}
