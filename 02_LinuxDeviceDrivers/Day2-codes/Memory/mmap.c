// ==============================
// Memory-Mapped Device Driver
// ==============================

#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

#define DEVICE_NAME "mmap_device"
#define PAGE_SIZE 4096

static char *kernel_buffer;
static dev_t dev_num;
static struct cdev mmap_cdev;

// Function to handle device open
static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "[mmap_device] Device opened\n");
    return 0;
}

// Function to handle device release
static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "[mmap_device] Device closed\n");
    return 0;
}

// Function to handle mmap
static int device_mmap(struct file *file, struct vm_area_struct *vma) {
    unsigned long pfn = virt_to_phys(kernel_buffer) >> PAGE_SHIFT;
    unsigned long size = vma->vm_end - vma->vm_start;

    if (size > PAGE_SIZE) {
        printk(KERN_ERR "[mmap_device] Requested size exceeds buffer size\n");
        return -EINVAL;
    }

    if (remap_pfn_range(vma, vma->vm_start, pfn, size, vma->vm_page_prot)) {
        printk(KERN_ERR "[mmap_device] Failed to map memory\n");
        return -EAGAIN;
    }

    printk(KERN_INFO "[mmap_device] Memory mapped successfully\n");
    return 0;
}

// File operations structure
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .mmap = device_mmap,
};

// Module initialization
static int __init mmap_device_init(void) {
    int result;

    // Allocate zeroed memory for the kernel buffer
    kernel_buffer = (char *)get_zeroed_page(GFP_KERNEL);
    if (!kernel_buffer) {
        printk(KERN_ERR "[mmap_device] Failed to allocate memory\n");
        return -ENOMEM;
    }

    // Allocate device number
    result = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (result < 0) {
        printk(KERN_ERR "[mmap_device] Failed to allocate device number\n");
        free_page((unsigned long)kernel_buffer);
        return result;
    }

    // Initialize character device
    cdev_init(&mmap_cdev, &fops);
    mmap_cdev.owner = THIS_MODULE;

    // Add character device to the system
    result = cdev_add(&mmap_cdev, dev_num, 1);
    if (result < 0) {
        printk(KERN_ERR "[mmap_device] Failed to add character device\n");
        unregister_chrdev_region(dev_num, 1);
        free_page((unsigned long)kernel_buffer);
        return result;
    }

    printk(KERN_INFO "[mmap_device] Module loaded, device number: %d\n", MAJOR(dev_num));
    return 0;
}

// Module cleanup
static void __exit mmap_device_exit(void) {
    cdev_del(&mmap_cdev);
    unregister_chrdev_region(dev_num, 1);
    free_page((unsigned long)kernel_buffer);
    printk(KERN_INFO "[mmap_device] Module unloaded\n");
}

module_init(mmap_device_init);
module_exit(mmap_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Memory-Mapped Device Driver Example");

/* ==============================
   Testing Guide for Memory-Mapped Device Driver
   ==============================
   
   **Step 1: Compile the Kernel Module**
   
   - Save the code as `mmap_device.c`.
   - Compile the kernel module using:
     ```
     make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
     ```
   - Load the module:
     ```
     sudo insmod mmap_device.ko
     ```
   - Check the kernel logs:
     ```
     dmesg | tail
     ```

   **Step 2: Create a Device File**
   
   - Create a device file in `/dev`:
     ```
     sudo mknod /dev/mmap_device c <major_number> 0
     ```
   - Replace `<major_number>` with the major number from the kernel logs.
   
   **Step 3: User-Space Application to Test mmap()**
   
   - Create a user-space program (`test_mmap.c`) to test the memory mapping:
     ```c
     
     ```
   
   **Step 4: Compile and Run the User-Space Program**
   
   - Compile the user-space program:
     ```
     gcc test_mmap.c -o test_mmap
     ```
   - Run the program:
     ```
     ./test_mmap
     ```

   **Step 5: Verify the Output**
   
   - Check the kernel logs to verify that the memory mapping was successful:
     ```
     dmesg | tail
     ```
   - You should see the message: `[mmap_device] Memory mapped successfully`.
   
   **Step 6: Unload the Kernel Module**
   
   - Unload the kernel module:
     ```
     sudo rmmod mmap_device
     ```
   - Remove the device file:
     ```
     sudo rm /dev/mmap_device
     ```
*/
