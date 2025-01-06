#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t data_ready;

void *prepare_data(void *arg) {
    printf("Thread 1: Preparing data packet...\n");
    sleep(2);  // Simulate data preparation
    printf("Thread 1: Data packet is ready.\n");

    // Signal that data is ready
    sem_post(&data_ready);
    return NULL;
}

void *send_data(void *arg) {
    printf("Thread 2: Waiting for data packet...\n");

    // Wait until data is ready
    sem_wait(&data_ready);

    printf("Thread 2: Data packet received. Sending to server...\n");
    sleep(1);  // Simulate data sending
    printf("Thread 2: Data packet sent to server.\n");

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the semaphore with a value of 0 (binary semaphore)
    sem_init(&data_ready, 0, 0);

    // Create threads
    pthread_create(&thread1, NULL, prepare_data, NULL);
    pthread_create(&thread2, NULL, send_data, NULL);

    // Wait for both threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the semaphore
    sem_destroy(&data_ready);

    return 0;
}
