/*\
 * Hello Driver --
 *
 * An hello world character device driver.*/

// LKM includes
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

// used by driver
#include <linux/device.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

// module info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("mets634");
MODULE_DESCRIPTION("Hello World Driver.");
MODULE_VERSION("1.0");

// driver variables
static char msg[] = "Hello World!!!";
static int size = sizeof(msg);
static unsigned int numberReads = 0;

// driver data
#define DEVICE_NAME = "hellochr"
#define CLASS_NAME = "hello"
static int major;
static struct class* cla = NULL;
static struct device* dev = NULL;

// driver functions prototype
static int dev_read(struct file *, char *, size_t, loff_t *);

// driver operations
static struct file_operations fops = {
	.read = dev_read,
};

static int __init dev_init(void) {
	// TODO: Error checking
	major = register_chrdev(0, DEVICE_NAME, &fops);
	cla = class_create(THIS_MODULE, CLASS_NAME);
	dev = device_create(cla, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
	return 0;
}

static void __exit dev_exit(void) {
	device_destroy(cla, MKDEV(major, 0));
	class_unregister(cla);
	class_destroy(cla);
	unregister_chrdev(major, DEVICE_NAME);
}

static ssize_t dev_read(struct file *filep, char *buffer, 
		size_t len, loff_t *offset) {
	copy_to_user(buffer, msg, size);
	return 0;
}

// register module entry and exit functions
module_init(dev_init);
module_exit(dev_exit);
