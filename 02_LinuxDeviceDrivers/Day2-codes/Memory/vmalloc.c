#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/vmalloc.h>  // For vmalloc and vfree
#include <linux/init.h>

#define MEM_SIZE (10 * 1024 * 1024)  // 10MB memory allocation

static char *vmalloc_buffer;

static int __init vmalloc_example_init(void) {
    printk(KERN_INFO "vmalloc_example: Module loading\n");

    // Allocate virtually contiguous memory
    vmalloc_buffer = vmalloc(MEM_SIZE);
    if (!vmalloc_buffer) {
        printk(KERN_ERR "vmalloc_example: vmalloc failed!\n");
        return -ENOMEM;
    }

    // Write data to the allocated buffer
    strcpy(vmalloc_buffer, "Hello from vmalloc");

    printk(KERN_INFO "vmalloc_example: Memory allocated at %px, data = %s\n",
           vmalloc_buffer, vmalloc_buffer);
    return 0;
}

static void __exit vmalloc_example_exit(void) {
    if (vmalloc_buffer) {
        printk(KERN_INFO "vmalloc_example: Freeing memory\n");
        vfree(vmalloc_buffer);
    }
    printk(KERN_INFO "vmalloc_example: Module unloaded\n");
}

module_init(vmalloc_example_init);
module_exit(vmalloc_example_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Example kernel module using vmalloc");
