#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "penis"

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
	.open = dev_open,
	.read = dev_read,
	.write = dev_write,
	.release = dev_release,
};

static int major;

static int __init penis_init(void) {
	major = register_chrdev(0, DEVICE_NAME, &fops);

	if (major < 0) {
		printk("Penis failed to load.\n");
		return major;
	}

	printk("Penis module initialized with major %d.\n", major);
	return 0;
}

static void __exit penis_exit(void) {
	unregister_chrdev(major, DEVICE_NAME);
	printk("Penis module exited.\n");
}

static int dev_open(struct inode *inodep, struct file *filep) {
	printk("Penis device opened.\n");
	return 0;
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len,
						 loff_t *offset) {
	printk("Failed to write to penis, which is read-only.\n");
	return -EFAULT;
}

static int dev_release(struct inode *inodep, struct file *filep) {
	printk("Penis device closed.\n");
	return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len,
						loff_t *offset) {
	int errors = 0;
	char *message = "PENIS";
	int messageLength = strlen(message);

	return copy_to_user(buffer, message, messageLength) == 0 ? messageLength
															 : -EFAULT;
}

module_init(penis_init);
module_exit(penis_exit);