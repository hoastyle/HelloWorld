/* 
 * Example code for simplest driver
 */

/* header file */
#include <linux/init.h>
#include <linux/module.h>

//parameter guide
//sudo insmod hello_world param1=10
int param1 = 0;
module_param(param1, int, 0);

//parameter will be found in /sys/module/hello_world/parameter
static unsigned long buffer_size = 4196;
module_param(buffer_size, ulong, (S_IRUSR | S_IRGRP | S_IROTH));
MODULE_PARM_DESC(buffer_size, "Internal buffer size");

//__init和__exit？
static int __init hello_init(void)
{
	printk(KERN_INFO "param1 is %d\n", param1);
	printk(KERN_INFO "buffer_size is %lu\n", buffer_size);
	printk(KERN_INFO "Hello world\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "Bye world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Hao Liang <hao.c.code@gmail.com>");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("A simplest hello world module");
MODULE_ALIAS("A simplest module");
