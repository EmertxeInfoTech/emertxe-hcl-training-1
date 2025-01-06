
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("testfile.txt", O_RDWR | O_CREAT, 0666);
    write(fd, "Hello, mmap!", 12);

    char *data = mmap(NULL, 12, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("Data in memory-mapped file: %s\n", data);

    munmap(data, 12);
    close(fd);

    return 0;
}
