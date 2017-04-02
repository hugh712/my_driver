#include <linux/module.h>
static int debug_enable=0;
module_param(debug_enable, int, 0);
MODULE_PARM_DESC(debug_enable,"Enable module debug mode.");

static int __init hello_init(void)
{
	printk(KERN_INFO "Hello Example Init debug mode is %s\n", 
			debug_enable?"enabled":"disable");
	return 0;
}

static void __exit hello_exit(void)
{
	printk("Hello Example Exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("hugh");
MODULE_DESCRIPTION("Example");
MODULE_LICENSE("GPL");
