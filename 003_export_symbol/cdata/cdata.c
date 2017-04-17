#include <linux/module.h>
#include <linux/init.h>
#include "add_sub.h"

static long a=1;
static long b=1;
static int AddOrSub=1;
static int debug_enable=0;
module_param(debug_enable, int, 0);
MODULE_PARM_DESC(debug_enable,"Enable module debug mode.");

static int __init hello_init(void)
{
	long result=0;

	if (AddOrSub==1)
	{
		result=add_integer(a,b);
	}
	else
	{
		result=sub_integer(a,b);
	}

	printk(KERN_INFO "Hello Example Init debug mode is %s\n", 
			debug_enable?"enabled":"disable");

	printk(KERN_INFO "%ld %s %ld is %ld", a, AddOrSub==1?"add":"sub",
			b,result);

	return 0;
}

static void __exit hello_exit(void)
{
	printk("Hello Example Exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

module_param(a,long,S_IRUGO);
module_param(b,long,S_IRUGO);
module_param(AddOrSub,int,S_IRUGO);

MODULE_AUTHOR("hugh");
MODULE_DESCRIPTION("Example");
MODULE_LICENSE("GPL");
