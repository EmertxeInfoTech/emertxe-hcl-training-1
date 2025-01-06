
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];  // Pipe: fd[0] for reading, fd[1] for writing

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid1 == 0) {
        // First child process (executes 'ls')
        close(fd[0]);  // Close unused read end
        dup2(fd[1], STDOUT_FILENO);  // Redirect stdout to pipe write end
        close(fd[1]);

        execlp("ls", "ls", NULL);  // Execute 'ls' command
        perror("execlp failed");
        return 1;
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid2 == 0) {
        // Second child process (executes 'wc')
        close(fd[1]);  // Close unused write end
        dup2(fd[0], STDIN_FILENO);  // Redirect stdin to pipe read end
        close(fd[0]);

        execlp("wc", "wc", NULL);  // Execute 'wc' command
        perror("execlp failed");
        return 1;
    }

    // Parent process
    close(fd[0]);
    close(fd[1]);

    wait(NULL);  // Wait for first child
    wait(NULL);  // Wait for second child

    return 0;
}
