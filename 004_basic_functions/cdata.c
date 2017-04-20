#include <linux/module.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/init.h>
#include<linux/slab.h>
#include <linux/mm.h> 
#include <asm/io.h>
#include <asm/uaccess.h>


#define HELLO_MAJOR 234
#define VIRTUALDISK_SIZE 0x2000
#define MEM_CLEAR 0x1
#define PORT1_SET 0x2
#define PORT2_SET 0x3

#define PTK(fmt,arg...)	\
	printk(KERN_INFO "[HELLO]:" fmt"\n", ## arg)

static int debug_enable=0;
module_param(debug_enable, int, 0);
MODULE_PARM_DESC(debug_enable,"Enable module debug mode.");

struct file_operations hello_fops;

struct VirtualDisk
{
	//struct cdev cdevv;
	unsigned char mem[VIRTUALDISK_SIZE];
	int port1;
	long port2;
};


static int hello_open(struct inode *inode, struct file *file)
{
	struct VirtualDisk *disk_dev;
	PTK("open: successful");
	PTK("open: major number by MAJOR  is %d", MAJOR(inode->i_rdev));
	PTK("open: minor number by MINOR  is %d", MINOR(inode->i_rdev));
	PTK("open: use count is %d", module_refcount(THIS_MODULE));	

	disk_dev=(struct VirtualDisk *)kmalloc(sizeof(struct VirtualDisk), GFP_KERNEL);
	if(!disk_dev)
	{
		return -ENOMEM;
	}
	
	memset(disk_dev, 0, sizeof(struct VirtualDisk));
	file->private_data=(void *)disk_dev;

	return 0;
}

static int hello_release(struct inode *inode, struct file *file)
{
	PTK("release: successful");
	PTK("release: use count is %d", module_refcount(THIS_MODULE));	
	return 0;
}

static ssize_t hello_read(struct file *file, char *buf, size_t size, loff_t *ptr)
{
	unsigned long p=*ptr;
	unsigned int count=size;
	int ret=0;
	struct VirtualDisk *disk=(struct VirtualDisk*)file->private_data;

	if(p>=VIRTUALDISK_SIZE)
		return count ? - ENXIO:0;

	if(count > VIRTUALDISK_SIZE - p)
		count = VIRTUALDISK_SIZE - p;
	
	if(copy_to_user(buf,(void*)(disk->mem + p), count))
	{
		ret = -EFAULT;
	}
	else
	{
		*ptr+=count;
		ret=count;
		PTK("read %d byte(s) from %ld\n", count,p);
	}

	return ret;
}

static ssize_t hello_write(struct file *file, const char *buf, size_t count, loff_t *ppos)
{
	PTK("write: accepting zero bytes");
	return 0;
}

static loff_t hello_llseek(struct file *file, loff_t offset, int orig)
{
	loff_t ret =0;
	PTK("write: accepting zero bytes");
	return ret;
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
	llseek: hello_llseek,
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
