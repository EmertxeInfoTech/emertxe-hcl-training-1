#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>  // For kmalloc and kfree
#include <linux/init.h>

#define MEM_SIZE 1024  // 1KB memory allocation

static char *kmalloc_buffer;

static int __init kmalloc_example_init(void) {
    printk(KERN_INFO "kmalloc_example: Module loading\n");

    // Allocate physically contiguous memory
    kmalloc_buffer = kmalloc(MEM_SIZE, GFP_KERNEL);
    if (!kmalloc_buffer) {
        printk(KERN_ERR "kmalloc_example: kmalloc failed!\n");
        return -ENOMEM;
    }

    // Write data to the allocated buffer
    strcpy(kmalloc_buffer, "Hello from kmalloc");

    printk(KERN_INFO "kmalloc_example: Memory allocated at %px, data = %s\n",
           kmalloc_buffer, kmalloc_buffer);
    return 0;
}

static void __exit kmalloc_example_exit(void) {
    if (kmalloc_buffer) {
        printk(KERN_INFO "kmalloc_example: Freeing memory\n");
        kfree(kmalloc_buffer);
    }
    printk(KERN_INFO "kmalloc_example: Module unloaded\n");
}

module_init(kmalloc_example_init);
module_exit(kmalloc_example_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Example kernel module using kmalloc");
