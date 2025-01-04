#include <stdio.h>
#include <unistd.h>

int main() {
    fork();  // Creating a new process
    printf("Hello from the process! PID: %d\n", getpid());
    return 0;
}
