#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>


/* Meta Information*/

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YARON ");
MODULE_DESCRIPTION("Register a device nr . and implement some callback function");

/*
 * this function is called , when the device file is opened
 * this function is called , when the module is loaded into the kernel
 
 */

static int driver_open(struct inode *device_file , struct file *instance)
{
	printk("dev_nr - open was called!\n");
	return 0;
}

static int driver_close(struct inode *device_file , struct file *instance)
{
	printk("dev_nr - close was called\n");
	return 0;
}

static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close
};

#define MYMAJOR 90

static int __init ModuleInit(void)
{
	int retval = 0;
	printk("Hellow Kernel!!!\n");
	retval = register_chrdev(MYMAJOR, "dev_nr_driver",&fops);
	if(retval == 0)	
	{
		printk("dev_nr - register device number Major : %d , Minor : %d\n",MYMAJOR,0);

	}
	if(retval > 0)
	{
		printk("dev_nr - register device number Major : %d , Minor : %d\n",retval>>20,retval&0xfffff);

	}
	else
	{
		printk("dev_nr - could not register device!\n");
	}
	return 0;
}

/*
 *this function is callled , when the module is removed from the kernel

 * */
static void __exit ModuleExit(void)
{
	unregister_chrdev(MYMAJOR,"my_dev_nr");
	printk("GoodBye Kernel!\n");

}

module_init(ModuleInit);
module_exit(ModuleExit);



