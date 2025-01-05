#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_USERS 5
#define NUM_PRINTERS 3

sem_t printers;

void *use_printer(void *arg) {
    int user_id = *(int *)arg;

    printf("User %d is waiting for a printer...\n", user_id);

    // Wait for a printer to be available
    sem_wait(&printers);

    // Critical section: using a printer
    printf("User %d is using a printer.\n", user_id);
    sleep(2);  // Simulate time to use the printer

    // Release the printer
    printf("User %d has finished using the printer.\n", user_id);
    sem_post(&printers);

    return NULL;
}

int main() {
    pthread_t users[NUM_USERS];
    int user_ids[NUM_USERS];

    // Initialize the semaphore with the number of available printers
    sem_init(&printers, 0, NUM_PRINTERS);

    // Create threads for each user
    for (int i = 0; i < NUM_USERS; i++) {
        user_ids[i] = i + 1;
        pthread_create(&users[i], NULL, use_printer, &user_ids[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_USERS; i++) {
        pthread_join(users[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&printers);

    return 0;
}
