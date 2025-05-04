#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 20

// Shared buffer
int buffer[BUFFER_SIZE];
int in = 0; // Index for next item to produce
int out = 0; // Index for next item to consume

// Semaphores
sem_t empty;   // Counts empty buffer slots
sem_t full;    // Counts full buffer slots
pthread_mutex_t mutex; // Protects critical sections

void* producer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Produce item
        int item = rand() % 100;

        // Wait for an empty slot
        
        // Enter critical section
        

        // Add item to buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Producer produced: %d\n", item);

        // Leave critical section
        
        // Signal that a slot is full
        

        // Sleep for a random time
        usleep(rand() % 100000);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Wait for a full slot
        
        // Enter critical section
        

        // Consume item from buffer
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer consumed: %d\n", item);

        // Leave critical section
        
        // Signal that a slot is empty
        

        // Sleep for a random time
        usleep(rand() % 100000);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // Initially all slots are empty
    sem_init(&full, 0, 0);             // Initially no slots are full
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}