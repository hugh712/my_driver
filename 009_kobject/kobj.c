#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/stat.h>
#include <linux/fs.h>


#define PTK(fmt,arg...)	\
	printk(KERN_INFO "[HELLO]:" fmt"\n", ## arg)

void kobject_release(struct kobject *kobject);
ssize_t kobject_show(struct kobject *kobject, struct attribute *attr, char *buf);
ssize_t kobject_store(struct kobject *kobject, struct attribute *attr,const char *buf, size_t count);

struct kobject kobj_Parent;
struct kobject kobj1;
struct kobject kobj2;
struct kset *kset1;

static int mykset_uevent_filter(struct kset *kset, struct kobject *kobj)
{
//	struct kobj_type *ktype = get_ktype(kobj);

	return 0;
}

static int kset_uevent (struct kset *kset, struct kobject *kobj, struct kobj_uevent_env *env)
{
	int i=0;
	PTK("uevent: kobj %s. \n", kobj->name);

	while (i < env->envp_idx)
	{
		PTK("%s. \n", env->envp[i]);
		i++;
	}
	return 0;
}

static const struct kset_uevent_ops mykset_uevent_ops = {
	.filter = mykset_uevent_filter,
	.uevent = kset_uevent,
};

//for attribute
struct attribute attr1 = {
	.name = "kobject_type1",
	.mode = S_IRWXUGO,
};
struct attribute attr2 = {
	.name = "kobject_type2",
	.mode = S_IRWXUGO,
};
struct attribute attr3 = {
	.name = "kobject_type3",
	.mode = S_IRWXUGO,
};

static struct attribute *def_attrs1[]={
	&attr1,
	NULL,
};
static struct attribute *def_attrs2[]={
	&attr2,
	NULL,
};
static struct attribute *def_attrs3[]={
	&attr3,
	NULL,
};

static int hugh_bus_match(struct device *_dev, struct device_driver *_drv)
{
	PTK("call bus match");
	return 0;
}

static int hugh_bus_probe(struct device *dev)
{
	PTK("call bus probe");
	return 0;
}

static int hugh_bus_remove(struct device *dev)
{
	PTK("call bus remove");
	return 0;
}

static int hugh_bus_suspend(struct device *dev, pm_message_t state)
{
	PTK("call bus suspend");
	return 0;
}

static int hugh_bus_resume(struct device *dev)
{
	PTK("call bus resume");
	return 0;
}

static void hugh_bus_shutdown(struct device *dev)
{
	PTK("call bus shutdown");
}

struct bus_type mytest_bus_type = {
	.name		= "hugh_bus",
	.match		= hugh_bus_match,
	.probe		= hugh_bus_probe,
	.remove		= hugh_bus_remove,
	.suspend	= hugh_bus_suspend,
	.resume		= hugh_bus_resume,
	.shutdown	= hugh_bus_shutdown,
};

struct sysfs_ops obj_sysops={
	.show = kobject_show,
	.store = kobject_store,
};

struct kobj_type ktype1={
	.release=kobject_release,
	.sysfs_ops=&obj_sysops,
	.default_attrs=def_attrs1,
};
struct kobj_type ktype2={
	.release=kobject_release,
	.sysfs_ops=&obj_sysops,
	.default_attrs=def_attrs2,
};
struct kobj_type ktype3={
	.release=kobject_release,
	.sysfs_ops=&obj_sysops,
	.default_attrs=def_attrs3,
};

static int __init hello_init(void)
{
	PTK("bus register");
	bus_register(&mytest_bus_type);	

	PTK("kobject-parent init");
	kobject_init_and_add(&kobj_Parent, &ktype1, NULL, "kobject-Parent");

	PTK("kset1 register");
	kset1=kset_create_and_add("kset1",&mykset_uevent_ops,&kobj_Parent);

	PTK("kobject-1 init");
	kobject_init_and_add(&kobj1, &ktype1, NULL, "kobject-1");
	kobj1.parent = &kobj_Parent;	

	PTK("kobject-2 init");
	kobject_init_and_add(&kobj2, &ktype2, NULL, "kobject-2");
	kobj2.kset=kset1;

	return 0;
}

static void __exit hello_exit(void)
{
	PTK("kset - 1 exit");
	kset_unregister(kset1);	

	PTK("kobject - Parent exit");
	kobject_del(&kobj_Parent);

	PTK("kobject - 1 exit");
	kobject_del(&kobj1);

	PTK("kobject - 2 exit");
	kobject_del(&kobj2);

	PTK("mytest_bus exit");
	bus_unregister(&mytest_bus_type);
}

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
