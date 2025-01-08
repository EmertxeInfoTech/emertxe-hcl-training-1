#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];  // Mutexes representing forks

// Function for a philosopher to eat
void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left_fork = id;                         // Left fork index
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;  // Right fork index

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 3);

        // Pick up forks (Deadlock-free approach: Always pick the lower index fork first)
        if (id % 2 == 0) {
            pthread_mutex_lock(&forks[left_fork]);    // Pick up left fork
            pthread_mutex_lock(&forks[right_fork]);   // Pick up right fork
        } else {
            pthread_mutex_lock(&forks[right_fork]);   // Pick up right fork
            pthread_mutex_lock(&forks[left_fork]);    // Pick up left fork
        }

        // Eating
        printf("Philosopher %d is eating...\n", id);
        sleep(rand() % 2);

        // Put down forks
        pthread_mutex_unlock(&forks[left_fork]);      // Put down left fork
        pthread_mutex_unlock(&forks[right_fork]);     // Put down right fork

        printf("Philosopher %d finished eating...\n", id);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize mutexes (forks)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
