#include <linux/init.h> // for KERN_INFO
#include <linux/module.h> // for all kernel modules
#include <linux/kernel.h> // for __init  and __exit macros

// module info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("mets634");
MODULE_DESCRIPTION("Hello World Linux kernel module.");
MODULE_VERSION("1.0");

// module init
static int __init helloworld_init(void) {
	printk(KERN_INFO "Hello World module loaded!!!");
	return 0;
}

// module exit
static void __exit helloworld_exit(void) {
	printk(KERN_INFO "Hello World module unloaded!!!");
}

// set init and exit of module
module_init(helloworld_init);
module_exit(helloworld_exit);
