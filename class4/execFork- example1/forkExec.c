#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> // for fork()
//-------------------------------------------------
void do_parent() ;
void do_child() ;
//-------------------------------------------------
int main() {
	pid_t status = fork();
	if (status < 0) {
		perror("error in fork");
		exit(EXIT_FAILURE);
	}
	if (status > 0) {
		do_parent();
		return EXIT_SUCCESS;
	}
	else {
		do_child();
		return EXIT_SUCCESS;
	}
return EXIT_SUCCESS;
}
//-------------------------------------------------
void do_parent() {
	puts("HELLO");
	puts("FROM");
	puts("FATHER");
}
//-------------------------------------------------
void do_child() {
	char *args[] = { "program2", NULL} ;
	if (execv("program2", args) != 0) {
		perror("execvp() failed") ;
		exit(EXIT_FAILURE) ;
	}
	puts("hello");
	puts("from");
	puts("child");
}