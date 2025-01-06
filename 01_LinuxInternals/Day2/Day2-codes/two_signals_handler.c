
#include <stdio.h>
#include <signal.h>

void handle_signal(int signal) {
    if (signal == SIGINT) {
        printf("Caught SIGINT (Ctrl+C)\n");
    } else if (signal == SIGTSTP) {
        printf("Caught SIGTSTP (Ctrl+Z)\n");
    }
}

int main() {
    signal(SIGINT, handle_signal);
    signal(SIGTSTP, handle_signal);

    while (1) {
        printf("Running... Press Ctrl+C or Ctrl+Z\n");
        sleep(1);
    }
    return 0;
}
