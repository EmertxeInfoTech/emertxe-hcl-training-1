#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process: Executing 'ls' command\n");
        execlp("/bin/ls", "ls", "-l", NULL);  // Execute 'ls -l' command

        // If execlp fails
        perror("exec failed");
        return 1;
    } else {
        // Parent process
        wait(NULL);  // Wait for the child process to complete
        printf("Parent process: Child finished execution\n");
    }

    return 0;
}
