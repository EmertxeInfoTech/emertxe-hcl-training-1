
#include <stdio.h>
#include <signal.h>
#include <ucontext.h>
#include <stdlib.h>

void handle_sigsegv(int sig, siginfo_t *info, void *context) {
    printf("Segmentation Fault at address: %p\n", info->si_addr);
    exit(1);
}

int main() {
    struct sigaction action;
    action.sa_flags = SA_SIGINFO | SA_NOCLDWAIT;
    action.sa_sigaction = handle_sigsegv;
    sigaction(SIGSEGV, &action, NULL); // SIGCHLD

    int *ptr = (int *)0xABCD1234;  // Intentionally cause segmentation fault
    *ptr = 42;

    return 0;
}
