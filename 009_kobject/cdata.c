#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/stat.h>
#include <linux/fs.h>


#define HELLO_MAJOR 234
#define PTK(fmt,arg...)	\
	printk(KERN_INFO "[HELLO]:" fmt"\n", ## arg)

void kobject_release(struct kobject *kobject);
ssize_t kobject_show(struct kobject *kobject, struct attribute *attr, char *buf);
ssize_t kobject_store(struct kobject *kobject, struct attribute *attr,const char *buf, 
		size_t count);

static int debug_enable=0;
struct kobject kobj;
module_param(debug_enable, int, 0);
MODULE_PARM_DESC(debug_enable,"Enable module debug mode.");

struct attribute test_attr = {
	.name = "kobject_test",
	.mode = S_IRWXUGO,
};

static struct attribute *def_attrs[]={
	&test_attr,
	NULL,
};

struct sysfs_ops obj_sysops={
	.show = kobject_show,
	.store = kobject_store,
};

struct kobj_type ktype={
	.release=kobject_release,
	.sysfs_ops=&obj_sysops,
	.default_attrs=def_attrs,
};

struct file_operations hello_fops;

static int hello_open(struct inode *inode, struct file *file)
{
	PTK("open: successful");
	PTK("open: major number by MAJOR  is %d", MAJOR(inode->i_rdev));
	PTK("open: minor number by MINOR  is %d", MINOR(inode->i_rdev));
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

	PTK("kobject init");
	kobject_init_and_add(&kobj, &ktype, NULL, "kobject_test");

	return 0;
}

static void __exit hello_exit(void)
{
	PTK("Hello Example Exit\n");
	unregister_chrdev(HELLO_MAJOR, "cdata");

	PTK("kobject exit");
	kobject_del(&kobj);
}

struct file_operations hello_fops = {
	owner: THIS_MODULE,
	read: hello_read,
	write: hello_write,
	unlocked_ioctl: hello_ioctl,
	open: hello_open,
	release: hello_release,
};

void kobject_release(struct kobject *kobject)
{
	PTK("kobject test: kobject_release");
}

ssize_t kobject_show(struct kobject *kobject, struct attribute *attr, char *buf)
{
	PTK("call kobject_show()");
	PTK("attrname:%s", attr->name);
	sprintf(buf,"%s\n", attr->name);
	return strlen(attr->name)+2;
}
ssize_t kobject_store(struct kobject *kobject, struct attribute *attr,const char *buf, 
		size_t count)
{
	PTK("call kobject_store");
	PTK("write: %s", buf);
	//strcpy(attr->name, buf);
	return count;
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("hugh");
MODULE_DESCRIPTION("Example");
MODULE_LICENSE("GPL");
