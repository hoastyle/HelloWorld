/* 
 * Example code for simplest driver
 */

/* header file */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>

//parameter guide
//sudo insmod hello_world param1=10
int param1 = 0;
module_param(param1, int, 0);

//parameter will be found in /sys/module/hello_world/parameter
static unsigned long buffer_size = 4196;
module_param(buffer_size, ulong, (S_IRUSR | S_IRGRP | S_IROTH));
MODULE_PARM_DESC(buffer_size, "Internal buffer size");

static struct cdev chr_dev;
static dev_t ndev;

static int chr_open(struct inode *nd, struct file *filp)
{
	int major = MAJOR(nd->i_rdev);
	int minor = MINOR(nd->i_rdev);
	printk(KERN_INFO "chr_open, major is %d, minor is %d\n", major, minor);
	return 0;
}

//owner?
struct file_operations chr_ops = {
	.owner = THIS_MODULE,
	.open = chr_open,
	//.read = chr_read,
};

//__init和__exit？
static int __init hello_init(void)
{
	int ret;
	cdev_init(&chr_dev, &chr_ops);
	ret = alloc_chrdev_region(&ndev, 0, 1, "chr_dev");
	if (ret < 0)
		return ret;

	ret = cdev_add(&chr_dev, ndev, 1);
	if (ret < 0)
		return ret;

	printk(KERN_INFO "Hello world\n");
	printk(KERN_INFO "major is %d, minor is %d\n", MAJOR(ndev), MINOR(ndev));
	printk(KERN_INFO "param1 is %d\n", param1);
	printk(KERN_INFO "buffer_size is %lu\n", buffer_size);
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "Bye world\n");
	cdev_del(&chr_dev);
	unregister_chrdev_region(ndev, 1);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Hao Liang <hao.c.code@gmail.com>");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("A simplest hello world module");
MODULE_ALIAS("A simplest module");
