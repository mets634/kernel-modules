#include <linux/kernel.h> 
#include <linux/module.h>
#include <linux/init.h>

// module info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("mets634");
MODULE_DESCRIPTION("A kernel module that will echo parameter into log file.");
MODULE_VERSION("1.0");

// setup module parameter
static char* msg = "default msg";
module_param(msg, charp, S_IRUGO);
MODULE_PARM_DESC(msg, "The msg to be echoed into log file.");

// init and exit functions

static int __init echo_init(void) {
	printk(KERN_INFO "Echoing --> %s", msg);
	return 0;
}

static void __exit echo_exit(void) {
	printk(KERN_INFO "Unloading echo module...");
}

// setup init and exit of module
module_init(echo_init);
module_exit(echo_exit);
