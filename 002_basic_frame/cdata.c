/*
 * codes from embedded Linux Primer Second Edition
 */
#include <linux/module.h>
#include <linux/fs.h>

#define HELLO_MAJOR 234
#define PTK(fmt,arg...)	\
	printk(KERN_INFO "[HELLO]:" fmt"\n", ## arg)

static int debug_enable=0;
module_param(debug_enable, int, 0);
MODULE_PARM_DESC(debug_enable,"Enable module debug mode.");

struct file_operations hello_fops;

static int hello_open(struct inode *inode, struct file *file)
{
	PTK("open: successful");
	PTK("open: major number by MAJOR  is %d", MAJOR(inode->i_rdev));
	PTK("open: minor number by MINOR  is %d", MINOR(inode->i_rdev));
	PTK("open: major number by imajor is %d", imajor(inode));
	PTK("open: minor number by iminor is %d", iminor(inode));
	PTK("open: use count is %d", module_refcount(THIS_MODULE));	
	return 0;
}

static int hello_release(struct inode *inode, struct file *file)
{
	PTK("release: successful");
	PTK("release: use count is %d", module_refcount(THIS_MODULE));	
	return 0;
}

static ssize_t hello_read(struct file *file, char *bug, size_t count, loff_t *ptr)
{
	PTK("read: returning zero byte");
	return 0;
}

static ssize_t hello_write(struct file *file, const char *buf, size_t count, loff_t *ppos)
{
	PTK("write: accepting zero bytes");
	return 0;
}

static long hello_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	PTK("ioctl: cmd=%u, arg=%lu", cmd, arg);
	return 0;
}

static int __init hello_init(void)
{
	int ret;
	PTK("init: Hello Example Init debug mode is %s", 
			debug_enable?"enabled":"disable");

	ret=register_chrdev(HELLO_MAJOR, "cdata", &hello_fops);
	if(ret < 0)
	{
		PTK("init: Error registering hello device\n");
		return ret;
	}
	PTK("init: registered moule successfully!\n");
	return 0;
}

static void __exit hello_exit(void)
{
	PTK("Hello Example Exit\n");
	unregister_chrdev(HELLO_MAJOR, "cdata");
}

struct file_operations hello_fops = {
	owner: THIS_MODULE,
	read: hello_read,
	write: hello_write,
	unlocked_ioctl: hello_ioctl,
	open: hello_open,
	release: hello_release,
};

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("hugh");
MODULE_DESCRIPTION("Example");
MODULE_LICENSE("GPL");
