#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    const char filename[] = "file1.txt";
    int n = 0;
    int i;
    pid_t pid = fork();

    FILE *file = fopen(filename, "r");
    if (file == 0)
    {
        fprintf(stderr, "Failed to open file '%s' \n", filename);
        exit(1);
    }
    if (pid == 0)
    {
        printf("I am a child with pid %d\n", getpid());

        while (fscanf(file, "%d", &n) == 1){
            printf("Child\n");
            printf("%d\n", n);
            sleep(1);
        }
    }
    else{
        printf("I am a parent with pid %d\n", getpid());
        while (fscanf(file, "%d", &n) == 1){
            printf("Parent\n");
            printf("%d\n", n);
            sleep(1);
        }
    }
    fclose(file);
    return EXIT_SUCCESS;
}