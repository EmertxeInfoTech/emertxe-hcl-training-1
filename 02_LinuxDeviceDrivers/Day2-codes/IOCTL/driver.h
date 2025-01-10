#ifndef DRIVER_IOCTL_H
#define DRIVER_IOCTL_H

// Device file path
#define DEVICE_FILE "/dev/mychar0"

// Buffer size for read/write operations
#define BUFFER_SIZE 1024

// IOCTL command macros
#define IOCTL_RESET_BUFFER _IO('a', 1)
#define IOCTL_GET_BUFFER_SIZE _IOR('a', 2, int)
#define IOCTL_SET_BUFFER_SIZE _IOW('a', 3, int)

// Menu option macros
#define MENU_OPEN_DEVICE       1
#define MENU_WRITE_DEVICE      2
#define MENU_READ_DEVICE       3
#define MENU_IOCTL_RESET       4
#define MENU_IOCTL_GET_SIZE    5
#define MENU_IOCTL_SET_SIZE    6
#define MENU_CLOSE_DEVICE      7
#define MENU_EXIT              8

#endif // DRIVER_IOCTL_H
