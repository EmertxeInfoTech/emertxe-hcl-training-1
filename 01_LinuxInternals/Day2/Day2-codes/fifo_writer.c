
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    mkfifo("myfifo", 0666);
    int fd = open("myfifo", O_WRONLY);
    char msg[] = "Hello from Writer";
    write(fd, msg, sizeof(msg));
    close(fd);
    return 0;
}
