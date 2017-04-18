#include <linux/module.h>
#include <linux/init.h>
#include "add_sub.h"

static int a=1;
static int b=1;
static int AddOrSub=1;

static int __init hello_init(void)
{
	int result=0;

	if (AddOrSub==1)
	{
		result=add_integer(a,b);
	}
	else
	{
		result=sub_integer(a,b);
	}

	printk(KERN_INFO "%d %s %d is %d", a, AddOrSub==1?"add":"sub",
			b,result);

	return 0;
}

static void __exit hello_exit(void)
{
	printk("Hello Example Exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

module_param(a,int,S_IRUGO);
module_param(b,int,S_IRUGO);
module_param(AddOrSub,int,S_IRUGO);

MODULE_AUTHOR("hugh");
MODULE_DESCRIPTION("Example");
MODULE_LICENSE("GPL");
