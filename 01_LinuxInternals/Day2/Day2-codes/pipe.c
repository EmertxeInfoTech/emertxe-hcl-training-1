
#include <stdio.h>
#include <unistd.h>

int main() {
    int fds[2];
    
    pipe(fds);
    // fds[0] -> read fd
    // fds[1] -> write fd

    pid_t pid = fork();
    if(pid > 0)
    {
            close(fds[0]);
            write(fds[1], "Hello, Welcome..!\n", 18);
    }
    else if(pid == 0)
    {
        close(fds[1]);
        char buffer[20];
        read(fds[0], buffer, 20);
        printf("From parent : %s", buffer);
    }
    
    return 0;
}
