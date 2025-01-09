#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/uaccess.h>
#include <linux/io.h>

#define DEVICE_NAME "keyboard_scancode"
#define IRQ_KEYBOARD 1   // IRQ number for the keyboard
#define BUFFER_SIZE 16   // Size of the scancode buffer

static int major_number;
static char scancode_buffer[BUFFER_SIZE];
static int buffer_pos = 0;
static int scancode_ready = 0;

static DEFINE_SPINLOCK(buffer_lock);  // Protect buffer access

// Interrupt handler for keyboard IRQ
static irqreturn_t keyboard_irq_handler(int irq, void *dev_id) {
    unsigned char scancode;

    // Read the scancode from the keyboard's I/O port (0x60)
    scancode = inb(0x60);

    spin_lock(&buffer_lock);

    if (buffer_pos < BUFFER_SIZE) {
        scancode_buffer[buffer_pos++] = scancode;
        scancode_ready = 1;
    }

    spin_unlock(&buffer_lock);

    return IRQ_HANDLED;
}

// Open function
static int dev_open(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "keyboard_scancode: Device opened\n");
    return 0;
}

// Read function
static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int bytes_to_copy;

    // Wait until a scancode is ready
    if (!scancode_ready) {
        return 0;
    }

    spin_lock(&buffer_lock);

    // Copy scancodes to user space
    bytes_to_copy = min(len, (size_t)buffer_pos);
    if (copy_to_user(buffer, scancode_buffer, bytes_to_copy)) {
        spin_unlock(&buffer_lock);
        return -EFAULT;
    }

    buffer_pos = 0;
    scancode_ready = 0;

    spin_unlock(&buffer_lock);

    return bytes_to_copy;
}

// Release function
static int dev_release(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "keyboard_scancode: Device closed\n");
    return 0;
}

// File operations structure
static struct file_operations fops = {
    .open = dev_open,
    .read = dev_read,
    .release = dev_release,
};

// Module initialization
static int __init keyboard_scancode_init(void) {
    int result;

    // Register character device
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "keyboard_scancode: Failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "keyboard_scancode: Registered with major number %d\n", major_number);

    // Request IRQ for the keyboard
    result = request_irq(IRQ_KEYBOARD, keyboard_irq_handler, IRQF_SHARED, DEVICE_NAME, (void *)(keyboard_irq_handler));
    if (result) {
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "keyboard_scancode: Failed to request IRQ\n");
        return result;
    }
    printk(KERN_INFO "keyboard_scancode: IRQ %d registered\n", IRQ_KEYBOARD);

    return 0;
}

// Module cleanup
static void __exit keyboard_scancode_exit(void) {
    // Free IRQ
    free_irq(IRQ_KEYBOARD, (void *)(keyboard_irq_handler));

    // Unregister character device
    unregister_chrdev(major_number, DEVICE_NAME);

    printk(KERN_INFO "keyboard_scancode: Module removed\n");
}

module_init(keyboard_scancode_init);
module_exit(keyboard_scancode_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Emertxe Info Tech");
MODULE_DESCRIPTION("Simple char driver to read keyboard scancodes using interrupts");
