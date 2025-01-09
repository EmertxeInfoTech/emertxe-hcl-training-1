#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define DEVICE_FILE "/dev/mychar0"
#define BUFFER_SIZE 1024

int main() {
    int fd = -1;
    int choice;
    char buffer[BUFFER_SIZE];

    do {
        printf("\nMenu:\n");
        printf("1. Open Device\n");
        printf("2. Write to Device\n");
        printf("3. Read from Device\n");
        printf("4. Close Device\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left in the buffer

        switch (choice) {
            case 1:
                if (fd >= 0) {
                    printf("Device already opened.\n");
                } else {
                    fd = open(DEVICE_FILE, O_RDWR);
                    if (fd < 0) {
                        perror("Failed to open the device file");
                    } else {
                        printf("Device file opened successfully: %s\n", DEVICE_FILE);
                    }
                }
                break;

            case 2:
                if (fd < 0) {
                    printf("Please open the device first.\n");
                } else {
                    printf("Enter the string to write to the device: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character

                    ssize_t bytes_written = write(fd, buffer, strlen(buffer));
                    if (bytes_written < 0) {
                        perror("Failed to write to device");
                    } else {
                        printf("Wrote %zd bytes to the device: %s\n", bytes_written, buffer);
                    }
                }
                break;

            case 3:
                if (fd < 0) {
                    printf("Please open the device first.\n");
                } else {
                    size_t size;
                    printf("Enter the number of bytes to read: ");
                    scanf("%zu", &size);
                    getchar(); // Consume newline character

                    if (size > BUFFER_SIZE - 1) {
                        printf("Size too large. Maximum allowed: %d\n", BUFFER_SIZE - 1);
                        break;
                    }

                    ssize_t bytes_read = read(fd, buffer, size);
                    if (bytes_read < 0) {
                        perror("Failed to read from device");
                    } else {
                        buffer[bytes_read] = '\0'; // Null-terminate the buffer
                        printf("Read %zd bytes from the device: %s\n", bytes_read, buffer);
                    }
                }
                break;

            case 4:
                if (fd < 0) {
                    printf("Device is not open.\n");
                } else {
                    if (close(fd) < 0) {
                        perror("Failed to close the device file");
                    } else {
                        printf("Device file closed successfully\n");
                        fd = -1;
                    }
                }
                break;

            case 5:
                if (fd >= 0) {
                    printf("Closing the device before exiting...\n");
                    if (close(fd) < 0) {
                        perror("Failed to close the device file");
                    } else {
                        printf("Device file closed successfully\n");
                    }
                }
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
