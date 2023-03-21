/* for module load */
#include <linux/init.h>
#include <linux/module.h>

/* for dev_t class */
#include <linux/types.h>

/* register and unregister device */
#include <linux/fs.h>

/* for operating dev_t */
#include <linux/kdev_t.h>

/* for error code */
#include <linux/errno.h>

/* for cdev */
#include <linux/cdev.h>

#include "scull.h"		/* local definitions */

int scull_minor =   0;
int scull_nr_devs = SCULL_NR_DEVS;	/* number of bare scull devices */
int scull_major =   SCULL_MAJOR;

MODULE_AUTHOR("Liu Feihong");
MODULE_LICENSE("Dual BSD/GPL");

int __init scull_init_module(void) {
    int result;
    dev_t dev = 0;

    result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs,
				"scull");
    scull_major = MAJOR(dev);

    return 0;
}


void __exit scull_cleanup_module(void) {

	dev_t devno = MKDEV(scull_major, scull_minor);

	unregister_chrdev_region(devno, scull_nr_devs);

}

module_init(scull_init_module);
module_exit(scull_cleanup_module);
