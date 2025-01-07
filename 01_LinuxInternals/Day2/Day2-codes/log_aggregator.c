#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    // Create shared memory
    key_t key = ftok("logfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    char *shared_memory = (char *)shmat(shmid, NULL, 0);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        // First child process simulates a service generating logs
        for (int i = 1; i <= 5; i++) {
            sprintf(shared_memory, "Service1: Log entry %d\n", i);
            sleep(1);
        }
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Second child process simulates another service generating logs
        for (int i = 1; i <= 5; i++) {
            sprintf(shared_memory, "Service2: Log entry %d\n", i);
            sleep(2);
        }
        exit(0);
    }

    // Parent process acts as the log aggregator
    for (int i = 0; i < 10; i++) {
        printf("Log Aggregator: %s", shared_memory);
        sleep(1);
    }

    // Cleanup
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
