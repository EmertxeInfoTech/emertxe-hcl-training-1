#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

int __init init_module(void) /* Constructor */
{
	printk(KERN_ERR "mfd registered\n");
	return 0;
}

void __exit cleanup_module(void) /* Destructor */
{
	printk(KERN_ERR "mfd unregistered\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Emertxe Info Tech <embedded.courses@emertxe.com>");
MODULE_DESCRIPTION("My First Driver");
