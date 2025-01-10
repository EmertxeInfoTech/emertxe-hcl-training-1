#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/uaccess.h>

#define FIRST_MINOR 0
#define MINOR_CNT 1

#define MAX_SIZE 1000

// Define ioctl commands
#define IOCTL_RESET_BUFFER _IO('a', 1)
#define IOCTL_GET_BUFFER_SIZE _IOR('a', 2, int)
#define IOCTL_SET_BUFFER_SIZE _IOW('a', 3, int)

static dev_t dev;
static struct cdev c_dev;
static struct class *cl;

static char k_buf[MAX_SIZE];
static int buffer_size = MAX_SIZE;

static int my_open(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: Open\n");
    return 0;
}

static int my_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: Close\n");
    return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver: In read\n");

    if (*off + len > buffer_size)
    {
        printk(KERN_WARNING "In read: Not enough data available\n");
        return 0;
    }

    if (copy_to_user(buf, k_buf + *off, len))
    {
        return -EFAULT;
    }

    printk(KERN_INFO "%zu bytes read\n", len);
    *off = *off + len;
    return len;
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver: In write\n");

    if (copy_from_user(k_buf, buf, len))
    {
        return -EFAULT;
    }

    printk(KERN_INFO "%zu bytes written\n", len);
    buffer_size = len;
    return len;
}

// Implement ioctl function
static long my_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
{
    switch (cmd)
    {
    case IOCTL_RESET_BUFFER:
        memset(k_buf, 0, buffer_size);
        printk(KERN_INFO "Buffer reset\n");
        break;

    case IOCTL_GET_BUFFER_SIZE:
        if (copy_to_user((int __user *)arg, &buffer_size, sizeof(buffer_size)))
        {
            return -EFAULT;
        }
        printk(KERN_INFO "Buffer size sent to user: %d\n", buffer_size);
        break;

    case IOCTL_SET_BUFFER_SIZE:
        if (copy_from_user(&buffer_size, (int __user *)arg, sizeof(buffer_size)))
        {
            return -EFAULT;
        }
        printk(KERN_INFO "Buffer size set to: %d\n", buffer_size);
        break;

    default:
        return -EINVAL;
    }
    return 0;
}

static struct file_operations driver_fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write = my_write,
    .unlocked_ioctl = my_ioctl, // Add ioctl support
};

static int __init fcd_init(void)
{
    int ret;
    struct device *dev_ret;

    if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "final_driver")) < 0)
    {
        return ret;
    }

    cdev_init(&c_dev, &driver_fops);

    if ((ret = cdev_add(&c_dev, dev, MINOR_CNT)) < 0)
    {
        unregister_chrdev_region(dev, MINOR_CNT);
        return ret;
    }

    if (IS_ERR(cl = class_create(THIS_MODULE, "char")))
    {
        cdev_del(&c_dev);
        unregister_chrdev_region(dev, MINOR_CNT);
        return PTR_ERR(cl);
    }

    if (IS_ERR(dev_ret = device_create(cl, NULL, dev, NULL, "mychar%d", 0)))
    {
        class_destroy(cl);
        cdev_del(&c_dev);
        unregister_chrdev_region(dev, MINOR_CNT);
        return PTR_ERR(dev_ret);
    }

    printk(KERN_INFO "Driver initialized\n");
    return 0;
}

static void __exit fcd_exit(void)
{
    device_destroy(cl, dev);
    class_destroy(cl);
    cdev_del(&c_dev);
    unregister_chrdev_region(dev, MINOR_CNT);
    printk(KERN_INFO "Driver removed\n");
}

module_init(fcd_init);
module_exit(fcd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Emertxe Info Tech <embedded.courses@emertxe.com>");
MODULE_DESCRIPTION("A Character Driver with IOCTL support");
