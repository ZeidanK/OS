#include <stdio.h> /* standard I/O routines  */
#include <pthread.h>/* pthread functions and data structures */

#define NUM_THREADS 5

/* function to be executed by the new thread */
void* printHello(void* threadID)
{
    long tid;
    tid = (long)threadID;
    printf("Hello from Thread #%ld!\n", tid);
    pthread_exit(NULL);
}
/* like any C program, program's execution begins in main */
int main()
{
    pthread_t threads[NUM_THREADS]; /* array of thread's ID (just an integer)          */
    int rc;/* return value */
    long t;/* data passed to the new thread */

    /* create a new threads that will execute 'printHello' */
    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Creating thread #%ld\n", t);
        rc = pthread_create(&threads[t], NULL, printHello, (void*)t);
        if (rc)/* could not create thread */
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            pthread_exit(NULL);/* terminate the thread */
        }
    }

    pthread_exit(NULL);
}