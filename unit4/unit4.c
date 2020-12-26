#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/param.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nayanjeet");
MODULE_DESCRIPTION("LKM to log messages into /var/log/messages !");

char *string="helloNayanjeet";
module_param(string,charp,S_IRUSR);
MODULE_PARM_DESC(string, "A string");

int init_module(void)
{
    printk(KERN_INFO "%s\n",string);
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Module Testing Complete\n");
}
