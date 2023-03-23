#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("Dual BSD/GPL");

static int howmany = 2;

module_param(howmany, int, S_IRUGO);

static int hello_init(void)
{
    int i;
    pr_info("------------- hellop init -----------------\n");
    for (i = 0; i < howmany; i++)
        printk(KERN_WARNING "Hello, world\n");
    printk(KERN_INFO "The process is \"%s\" (pid %i)\n", 
            current->comm, current->pid);
    pr_info("Linux version: %d\n", LINUX_VERSION_CODE);
    pr_info("UTS_RELEASE: %s\n", UTS_RELEASE);
    pr_info("------------- hellop init -----------------\n");
    return 0;
}

static void hello_exit(void)
{
    pr_info("------------- hellop exit -----------------\n");
    printk(KERN_WARNING "Goodbye, cruel world\n");
    pr_info("------------- hellop exit -----------------\n");
}

module_init(hello_init);
module_exit(hello_exit);

