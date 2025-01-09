#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_ENTRY_NAME "simple_proc_entry"

static int proc_value = 0;  // The variable we will expose via /proc
static struct proc_dir_entry *proc_entry;

// Function to handle read operation from /proc
static ssize_t proc_read(struct file *file, char __user *buf, size_t count, loff_t *pos)
{
    char buffer[64];
    int len;

    // Prevent multiple reads
    if (*pos > 0)
        return 0;

    // Prepare the data to be read
    len = sprintf(buffer, "%d\n", proc_value);

    // Copy the data to userspace
    if (copy_to_user(buf, buffer, len))
        return -EFAULT;

    // Update the file position
    *pos += len;

    return len;
}

// Function to handle write operation to /proc
static ssize_t proc_write(struct file *file, const char __user *buf, size_t count, loff_t *pos)
{
    char buffer[64];

    // Limit input size
    if (count > sizeof(buffer) - 1)
        return -EINVAL;

    // Copy the data from userspace
    if (copy_from_user(buffer, buf, count))
        return -EFAULT;

    // Null-terminate the input and convert it to an integer
    buffer[count] = '\0';
    sscanf(buffer, "%d", &proc_value);

    return count;
}

// Define file operations for the proc entry
static const struct proc_ops proc_fops = {
    .proc_read = proc_read,
    .proc_write = proc_write,
};

// Module initialization function
static int __init simple_proc_init(void)
{
    // Create a proc entry at /proc/simple_proc_entry
    proc_entry = proc_create(PROC_ENTRY_NAME, 0666, NULL, &proc_fops);
    if (!proc_entry) {
        pr_err("Failed to create /proc/%s\n", PROC_ENTRY_NAME);
        return -ENOMEM;
    }

    pr_info("/proc/%s created.\n", PROC_ENTRY_NAME);
    return 0;
}

// Module cleanup function
static void __exit simple_proc_exit(void)
{
    // Remove the proc entry
    proc_remove(proc_entry);
    pr_info("/proc/%s removed.\n", PROC_ENTRY_NAME);
}

module_init(simple_proc_init);
module_exit(simple_proc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Emertxe Info Tech");
MODULE_DESCRIPTION("A simple procfs read/write example");
