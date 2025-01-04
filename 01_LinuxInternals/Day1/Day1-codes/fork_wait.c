#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
    } else {
        // Parent process
        wait(NULL);  // Wait for child process to finish
        printf("Parent process: PID = %d, Child PID = %d finished\n", getpid(), pid);
    }
    return 0;
}
