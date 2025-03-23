#include <stdio.h>
#include <unistd.h>
int main() {
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return -1;
  } else if (pid == 0) {
    printf("I am child\n");

    fflush(stdout);
  } else {
    printf("I am parent\n");

    fflush(stdout);
  }
  printf("my first test   \n");

  fflush(stdout);
  return 0;
}
