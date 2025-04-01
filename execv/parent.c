#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
  pid_t pid;
  int status;
  pid = fork();
  if (pid == 0) {
    // Child process
    printf("Child process (PID: %d) executing another C program...\n",
           getpid());
    // Execute another compiled C program
    char *args[] = {"./child_program", "arg1", "arg2", "arg3", NULL};
    execv(args[0], args);
  } else {
    // Parent process
    printf("Parent process (PID: %d) is waiting for child (PID: %d)...\n",
           getpid(), pid);
    pid_t waited_pid = waitpid(pid, &status, 0);
    printf("Child process %d exited with status %d.\n", waited_pid, status);
  }
  return 0;
}
