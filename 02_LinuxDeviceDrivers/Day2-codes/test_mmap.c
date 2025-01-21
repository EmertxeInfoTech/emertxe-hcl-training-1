#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#define DEVICE_PATH "/dev/mmap_device"

int main() {
    int fd;
    char *mapped_memory;

    fd = open(DEVICE_PATH, O_RDWR);
        if (fd < 0) {
        perror("Failed to open device");
        return -1;
    }

    mapped_memory = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED) {
        perror("mmap failed");
        close(fd);
        return -1;
    }

    printf("Reading from memory-mapped area: %s\n", mapped_memory);
    sprintf(mapped_memory, "Hello from user space!");

    munmap(mapped_memory, 4096);
    close(fd);

    return 0;
}