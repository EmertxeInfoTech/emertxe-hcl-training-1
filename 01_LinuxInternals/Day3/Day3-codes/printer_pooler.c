#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SEM_KEY 0x1234

// Function to perform P (wait) operation on the semaphore
void sem_lock(int semid) {
    struct sembuf sb = {0, -1, 0};
    semop(semid, &sb, 1);
}

// Function to perform V (signal) operation on the semaphore
void sem_unlock(int semid) {
    struct sembuf sb = {0, 1, 0};
    semop(semid, &sb, 1);
}

// Function to simulate a print job
void print_job(int process_id) {
    printf("Process %d: Trying to access the printer...\n", process_id);
    
    sem_lock(semget(SEM_KEY, 1, 0));  // Lock the semaphore

    printf("Process %d: Printing...\n", process_id);
    sleep(2);  // Simulate print time

    printf("Process %d: Print job completed.\n", process_id);

    sem_unlock(semget(SEM_KEY, 1, 0));  // Unlock the semaphore
}

int main() {
    int semid = semget(SEM_KEY, 1, 0666 | IPC_CREAT);

    // Initialize the semaphore to 1 (unlocked)
    semctl(semid, 0, SETVAL, 1);

    if (fork() == 0) {
        // Child process 1
        print_job(1);
        exit(0);
    }

    if (fork() == 0) {
        // Child process 2
        print_job(2);
        exit(0);
    }

    if (fork() == 0) {
        // Child process 3
        print_job(3);
        exit(0);
    }

    // Wait for all child processes to complete
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    // Clean up the semaphore
    semctl(semid, 0, IPC_RMID);
    return 0;
}
