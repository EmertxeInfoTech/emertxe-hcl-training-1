#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child process: PID = %d, PPID = %d\n", getpid(), getppid());
    } else {
        // Parent process exits immediately
        printf("Parent process: PID = %d\n", getpid());
        sleep(5);  // Let the child process finish before parent exits
        execlp("ps", "ps", "-el", NULL);
    }
    return 0;
}
