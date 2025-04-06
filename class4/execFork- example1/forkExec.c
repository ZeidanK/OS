#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> // for wait()
#include <unistd.h>   // for fork()

//-------------------------------------------------
void do_parent();
void do_child();
//-------------------------------------------------
int main() {
  pid_t status = fork();
  if (status < 0) {
    perror("error in fork");
    exit(EXIT_FAILURE);
  }
  if (status > 0) { // this means we are in the parent
    do_parent();
    wait(NULL); // wait for the child to finish so the second program wont print
                // with the prompt
    return EXIT_SUCCESS;
  } else {
    do_child();
    return EXIT_SUCCESS;
  }
  return EXIT_SUCCESS;
}
//-------------------------------------------------
void do_parent() { // this function is for the parent
  puts("HELLO");
  puts("FROM");
  puts("FATHER");
}
//-------------------------------------------------
void do_child() { // the child will load the program2
  puts("hello");
  puts("from");
  puts("child");
  char *args[] = {"program2", NULL};
  if (execv("program2", args) != 0) {
    perror("execvp() failed");
    exit(EXIT_FAILURE);
  }
}
