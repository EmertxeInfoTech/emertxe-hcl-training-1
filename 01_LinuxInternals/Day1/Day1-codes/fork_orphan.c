#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        sleep(1);
        printf("Before parent terminate: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(5);  // Wait for parent to finish
        printf("After parent terminates: PID = %d, New PPID = %d\n", getpid(), getppid());
    } else {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());
    }
    return 0;
}
