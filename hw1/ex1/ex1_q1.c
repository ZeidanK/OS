#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
// just adding something for the git push
void *greet_one(char *who);

int main(int argc, char *argv[]) {
  /*ENTER YOUR CODE HERE*/
  // check waht the first argument is
  // // it can be ("multiproc","child","single")
  if (strcmp(argv[1], "multiproc") == 0) {
    // fork a child process
    for (int i = 2; i < argc; i++) {
      pid_t pid = fork();
      if (pid < 0) {
        fprintf(stderr, "Fork failed.\n");
        return 1;
      } else if (pid == 0) {
        // Child process
        char *args[] = {"hello_who", argv[i], NULL};
        if (execv("hello_who", args) != 0) {
          perror("execvp() failed");
          exit(EXIT_FAILURE);
        }

        greet_one(argv[i]);
        exit(0);
      } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish
      }
    }

  } else if (strcmp(argv[1], "child") == 0) {
    printf("child\n");
    for (int i = 2; i < argc; i++) {
      pid_t pid = fork();
      if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
      } else if (pid == 0) {
        // Child process
        greet_one(argv[i]);
        exit(0);
      } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish
        // greet_one(argv[i]);
      }
    }
  }

  else if (strcmp(argv[1], "single") == 0) {
    // for each of the othre arguments call the function greet greet_one

    printf("single\n");
    for (int i = 2; i < argc; i++) {
      greet_one(argv[i]);
    }
  }
  sleep(1);
  exit(0);
}

//-----------------------------------------------
void *greet_one(char *who) {
  printf("Hello %s !!  (pid=%d ppid=%d)\n", who, getpid(), getppid());
}
