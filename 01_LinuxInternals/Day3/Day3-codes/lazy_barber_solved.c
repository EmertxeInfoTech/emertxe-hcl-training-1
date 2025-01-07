#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SEM_KEY_CUSTOMER 0x1111  // Customer semaphore
#define SEM_KEY_BARBER   0x2222  // Barber semaphore
#define SEM_KEY_MUTEX    0x3333  // Mutex semaphore

#define NUM_CHAIRS 3  // Number of chairs in the waiting room
int waiting_customers = 0;

// Function to perform P (wait) operation on the semaphore
void sem_wait(int semid) {
    struct sembuf sb = {0, -1, 0};
    semop(semid, &sb, 1);
}

// Function to perform V (signal) operation on the semaphore
void sem_signal(int semid) {
    struct sembuf sb = {0, 1, 0};
    semop(semid, &sb, 1);
}

// Barber function
void *barber(void *arg) {
    int semid_customer = semget(SEM_KEY_CUSTOMER, 1, 0666);
    int semid_barber = semget(SEM_KEY_BARBER, 1, 0666);
    int semid_mutex = semget(SEM_KEY_MUTEX, 1, 0666);

    while (1) {
        // Wait for a customer to arrive
        sem_wait(semid_customer);

        // Lock mutex to access waiting customers count
        sem_wait(semid_mutex);
        waiting_customers--;
        printf("Barber: Cutting hair. Customers waiting: %d\n", waiting_customers);
        sem_signal(semid_mutex);

        // Signal the barber semaphore to cut hair
        sem_signal(semid_barber);

        // Simulate haircut time
        sleep(2);
    }
    return NULL;
}

// Customer function
void *customer(void *arg) {
    int semid_customer = semget(SEM_KEY_CUSTOMER, 1, 0666);
    int semid_barber = semget(SEM_KEY_BARBER, 1, 0666);
    int semid_mutex = semget(SEM_KEY_MUTEX, 1, 0666);

    // Lock mutex to access waiting customers count
    sem_wait(semid_mutex);
    if (waiting_customers < NUM_CHAIRS) {
        waiting_customers++;
        printf("Customer %ld: Waiting. Customers waiting: %d\n", (long)arg, waiting_customers);

        // Signal the customer semaphore to notify the barber
        sem_signal(semid_customer);

        // Unlock mutex
        sem_signal(semid_mutex);

        // Wait for the barber to finish cutting hair
        sem_wait(semid_barber);
        printf("Customer %ld: Got a haircut.\n", (long)arg);
    } else {
        printf("Customer %ld: No chair available. Leaving...\n", (long)arg);
        sem_signal(semid_mutex);
    }
    return NULL;
}

int main() {
    // Create semaphores
    int semid_customer = semget(SEM_KEY_CUSTOMER, 1, 0666 | IPC_CREAT);
    int semid_barber = semget(SEM_KEY_BARBER, 1, 0666 | IPC_CREAT);
    int semid_mutex = semget(SEM_KEY_MUTEX, 1, 0666 | IPC_CREAT);

    // Initialize semaphores
    semctl(semid_customer, 0, SETVAL, 0);  // No waiting customers initially
    semctl(semid_barber, 0, SETVAL, 0);    // Barber is sleeping initially
    semctl(semid_mutex, 0, SETVAL, 1);     // Mutex is unlocked initially

    // Create barber thread
    pthread_t barber_thread;
    pthread_create(&barber_thread, NULL, barber, NULL);

    // Simulate customers arriving at random times
    pthread_t customer_threads[10];
    for (long i = 0; i < 10; i++) {
        sleep(rand() % 3);
        pthread_create(&customer_threads[i], NULL, customer, (void *)i);
    }

    // Wait for all customer threads to complete
    for (int i = 0; i < 10; i++) {
        pthread_join(customer_threads[i], NULL);
    }

    // Clean up semaphores
    semctl(semid_customer, 0, IPC_RMID);
    semctl(semid_barber, 0, IPC_RMID);
    semctl(semid_mutex, 0, IPC_RMID);

    return 0;
}
