#include <stdio.h>   // For standard I/O functions
#include <stdlib.h>  // For exit() function
#include <string.h>  // For string manipulation functions like strtok()
#include <unistd.h>  // For fork(), execvp(), and related functions
#include <sys/types.h> // For pid_t type
#include <sys/wait.h>  // For wait() and waitpid()

// Define maximum size for user input and arguments
#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100

// Function to implement a simple shell
void simple_shell() {
    char input[MAX_INPUT_SIZE];  // Buffer to store user input
    char *args[MAX_ARG_SIZE];    // Array to hold arguments parsed from user input
    pid_t pid;                   // Process ID variable
    int status;                  // Status variable to hold child process exit status

    while (1) {
        // Display shell prompt
        printf("my_shell> ");
        fflush(stdout);  // Ensure prompt is displayed immediately

        // Read user input
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            perror("fgets failed");  // Handle error in reading input
            exit(1);
        }

        // Remove newline character from input (if any)
        input[strcspn(input, "\n")] = '\0';

        // Tokenize the input string into arguments using spaces as delimiters
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        // Check for the "exit" command to terminate the shell
        if (strcmp(args[0], "exit") == 0) {
            printf("Exiting shell...\n");
            break;
        }

        // Create a new process using fork()
        pid = fork();
        if (pid < 0) {
            // Fork failed
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process: Execute the command using execvp()
            if (execvp(args[0], args) == -1) {
                perror("Exec failed");  // Handle error if command execution fails
                exit(1);
            }
        } else {
            // Parent process: Wait for the child process to complete
            do {
                pid_t wpid = waitpid(pid, &status, WUNTRACED);  // Wait for child process
                if (wpid == -1) {
                    perror("Waitpid failed");
                    exit(1);
                }
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));  // Continue waiting if child hasn't exited or been signaled
        }
    }
}

int main() {
    // Start the simple shell
    simple_shell();
    return 0;
}
