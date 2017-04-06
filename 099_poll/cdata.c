/*
 * codes from embedded Linux Primer Second Edition
 */
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/poll.h>


#define dbg(fmt,args...) printk("[%s]:%d => "fmt,__FUNCTION__,__LINE__,##args)
#define DBG() printk("[%s]:%d => \n",__FUNCTION__,__LINE__)
#define HELLO_MAJOR 234

static int debug_enable=0;
module_param(debug_enable, int, 0);
MODULE_PARM_DESC(debug_enable,"Enable module debug mode.");

struct file_operations hello_fops;

struct cdata_t{
	int index;
	int wait;
	wait_queue_head_t read_wait;
};

static int hello_open(struct inode *inode, struct file *file)
{
	struct cdata_t *cdata;
	
	cdata = (struct cdata_t *)kmalloc(sizeof(struct cdata_t), GFP_KERNEL);
	cdata->index=0;
  init_waitqueue_head(&cdata->read_wait);
	file->private_data=(void *)cdata;

	printk("hello_open: successful\n");
	return 0;
}

static int hello_release(struct inode *inode, struct file *file)
{
	printk("hello_release: successful\n");
	return 0;
}

static ssize_t hello_read(struct file *file, char *bug, size_t count, loff_t *ptr)
{
	printk("hello_read: returning zero byte\n");
	return 0;
}

static ssize_t hello_write(struct file *file, const char *buf, size_t count, loff_t *ppos)
{
	printk("hello_write: accepting zero bytes\n");
	return 0;
}

static long hello_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	printk("hello_ioctl: cmd=%u, arg=%lu\n", cmd, arg);
	return 0;
}

static unsigned int hello_poll(struct file *file, poll_table *pt)
{
	unsigned int mask = POLLOUT;
	struct cdata_t *cdata;
	
  printk(KERN_INFO "call hello_poll");
	cdata=(struct cdata_t *)file->private_data;

	poll_wait(file,&cdata->read_wait ,pt);

	if(cdata->wait==1)
	{
		mask|=POLLIN | POLLRDNORM; //readable
	}

	return mask;

}

static int __init hello_init(void)
{
	int ret;
	printk(KERN_INFO "Hello Example Init debug mode is %s\n", 
			debug_enable?"enabled":"disable");

	ret=register_chrdev(HELLO_MAJOR, "cdata", &hello_fops);
	if(ret < 0)
	{
		printk("Error registering hello device\n");
		return ret;
	}
	printk("Hello: registered moule successfully!\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk("Hello Example Exit\n");
	unregister_chrdev(HELLO_MAJOR, "cdata");
}

struct file_operations hello_fops = {
	owner: THIS_MODULE,
	read: hello_read,
	write: hello_write,
	unlocked_ioctl: hello_ioctl,
	open: hello_open,
	poll: hello_poll,
	release: hello_release,
};

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("hugh");
MODULE_DESCRIPTION("Example");
MODULE_LICENSE("GPL");
