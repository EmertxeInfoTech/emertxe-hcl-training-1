#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

// Function for a philosopher to eat
void *philosopher(void *arg) {
    int id = *(int *)arg;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 3);

        // Pick up forks
        printf("Philosopher %d is hungry...\n", id);
        pthread_mutex_lock(&forks[id]);           // Pick up left fork
        pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]);  // Pick up right fork

        // Eat
        printf("Philosopher %d is eating...\n", id);
        sleep(rand() % 2);

        // Put down forks
        pthread_mutex_unlock(&forks[id]);         // Put down left fork
        pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]);  // Put down right fork

        printf("Philosopher %d finished eating...\n", id);
    }
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize forks (mutexes)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
