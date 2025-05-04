
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define MAX_COUNT 1000000

int counter = 0;
pthread_mutex_t counter_mutex;

// Thread function to increment the counter
void* increment_counter(void* arg) {
    int i;
    for (i = 0; i < MAX_COUNT; i++) {
        // Acquire the mutex lock before accessing the shared resource (counter)
        pthread_mutex_lock(&counter_mutex);

        // Critical section: Increment the counter
        counter++;

        // Release the mutex lock after accessing the shared resource
        pthread_mutex_unlock(&counter_mutex);
    }

    pthread_exit(NULL);
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    int i;

    // Initialize the mutex
    if (pthread_mutex_init(&counter_mutex, NULL) != 0) {
        perror("Mutex initialization failed");
        return 1;
    }

    // Create the threads
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
            perror("Thread creation failed");
            return 1;
        }
    }

    // Wait for the threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Thread join failed");
            return 1;
        }
    }

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);

    // Destroy the mutex
    pthread_mutex_destroy(&counter_mutex);

    return 0;
}