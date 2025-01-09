#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/string.h>

static int my_value = 0;  // The variable we will expose in sysfs

// Function to handle read operation from sysfs
static ssize_t my_value_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", my_value);
}

// Function to handle write operation to sysfs
static ssize_t my_value_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    sscanf(buf, "%d", &my_value);
    return count;
}

// Define the sysfs attribute structure
static struct kobj_attribute my_value_attribute = __ATTR(my_value, 0660, my_value_show, my_value_store);

static struct kobject *example_kobject;

// Module initialization function
static int __init simple_sysfs_init(void)
{
    int error;

    // Create a kobject in /sys/kernel/simple_sysfs
    example_kobject = kobject_create_and_add("simple_sysfs", kernel_kobj);
    if (!example_kobject)
        return -ENOMEM;

    // Create the sysfs file my_value under /sys/kernel/simple_sysfs
    error = sysfs_create_file(example_kobject, &my_value_attribute.attr);
    if (error) {
        pr_debug("failed to create the my_value file in /sys/kernel/simple_sysfs\n");
        return error;
    }

    pr_info("Simple sysfs module loaded.\n");
    return 0;
}

// Module cleanup function
static void __exit simple_sysfs_exit(void)
{
    // Remove the sysfs file and kobject
    kobject_put(example_kobject);
    pr_info("Simple sysfs module unloaded.\n");
}

module_init(simple_sysfs_init);
module_exit(simple_sysfs_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Emertxe Info Tech");
MODULE_DESCRIPTION("A simple sysfs read/write example");
