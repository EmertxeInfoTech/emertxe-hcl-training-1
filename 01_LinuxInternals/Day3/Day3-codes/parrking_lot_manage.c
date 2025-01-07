#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SEM_KEY 0x1234
#define PARKING_SPACES 3  // Number of parking spaces available

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

// Function to simulate a car entering the parking lot
void enter_parking_lot(int car_id, int semid) {
    printf("Car %d: Trying to park...\n", car_id);

    sem_wait(semid);  // Decrease semaphore (take a parking space)

    printf("Car %d: Parked successfully.\n", car_id);
    sleep(rand() % 5 + 1);  // Simulate time spent in the parking lot

    printf("Car %d: Leaving the parking lot.\n", car_id);
    sem_signal(semid);  // Increase semaphore (free a parking space)
}

int main() {
    int semid = semget(SEM_KEY, 1, 0666 | IPC_CREAT);

    // Initialize the semaphore to the number of parking spaces
    semctl(semid, 0, SETVAL, PARKING_SPACES);

    // Simulate 6 cars trying to park
    for (int i = 1; i <= 6; i++) {
        if (fork() == 0) {
            enter_parking_lot(i, semid);
            exit(0);
        }
    }

    // Wait for all child processes to complete
    for (int i = 1; i <= 6; i++) {
        wait(NULL);
    }

    // Clean up the semaphore
    semctl(semid, 0, IPC_RMID);
    return 0;
}
