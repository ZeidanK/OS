#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid;

  // Create a child process
  pid = fork();

  if (pid < 0) {
    // Fork failed
    fprintf(stderr, "Fork failed.\n");
    return 1;
  } else if (pid == 0) {
    // Child process
    printf("Child process executing...\n");

    // Replace child process with a new program
    char *args[] = {"pwd", NULL};

    execv("/bin/pwd", args);

    // execv() will not return if successful, unless there is an error
    fprintf(stderr, "execl failed.\n");
    return 1;
  } else {
    // Parent process
    printf("Parent process waiting for child to finish...\n");

    // Wait for the child to finish
    wait(NULL);

    printf("Child process finished.\n");
  }

  return 0;
}
