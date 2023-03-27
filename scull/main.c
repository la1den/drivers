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

int scull_major =   SCULL_MAJOR;
int scull_minor =   0;
int scull_nr_devs = SCULL_NR_DEVS;	/* number of bare scull devices */

module_param(scull_major, int, S_IRUGO);

MODULE_AUTHOR("Liu Feihong");
MODULE_LICENSE("Dual BSD/GPL");


int scull_trim(struct scull_dev *dev)
{
	struct scull_qset *next, *dptr;
	int qset = dev->qset;   /* "dev" is not-null */
	int i;

	for (dptr = dev->data; dptr; dptr = next) { /* all the list items */
		if (dptr->data) {
			for (i = 0; i < qset; i++)
				kfree(dptr->data[i]);
			kfree(dptr->data);
			dptr->data = NULL;
		}
		next = dptr->next;
		kfree(dptr);
	}
	dev->size = 0;
	dev->quantum = scull_quantum;
	dev->qset = scull_qset;
	dev->data = NULL;
	return 0;
}

int scull_open(struct inode *inode, struct file *filp)
{
	struct scull_dev *dev; /* device information */

	dev = container_of(inode->i_cdev, struct scull_dev, cdev);
	filp->private_data = dev; /* for other methods */

	/* now trim to 0 the length of the device if open was write-only */
	if ( (filp->f_flags & O_ACCMODE) == O_WRONLY) {
		scull_trim(dev); /* ignore errors */
	}
	return 0;          /* success */
}


int scull_release(struct inode *inode, struct file *filp)
{
	return 0;
}


struct file_operations scull_fops = {
	.owner =    THIS_MODULE,
	/* .llseek =   scull_llseek, */
	.read =     scull_read,
	.write =    scull_write,
	/* .ioctl =    scull_ioctl, */
	.open =     scull_open,
	.release =  scull_release,
};


/*
 * Set up the char_dev structure for this device.
 */
static void scull_setup_cdev(struct scull_dev *dev, int index)
{
	int err, devno = MKDEV(scull_major, scull_minor + index);
    
	cdev_init(&dev->cdev, &scull_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &scull_fops;
	err = cdev_add (&dev->cdev, devno, 1);
	/* Fail gracefully if need be */
	if (err)
		printk(KERN_NOTICE "Error %d adding scull%d", err, index);
}


int __init scull_init_module(void) {
    int result;
    dev_t dev = 0;

	if (scull_major) {
		dev = MKDEV(scull_major, scull_minor);
		result = register_chrdev_region(dev, scull_nr_devs, "scull");
	} else {
		result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs,
				"scull");
		scull_major = MAJOR(dev);
	}
	if (result < 0) {
		printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
		return result;
	}

    return 0;
}


void __exit scull_cleanup_module(void) {

	dev_t devno = MKDEV(scull_major, scull_minor);

	unregister_chrdev_region(devno, scull_nr_devs);

}

module_init(scull_init_module);
module_exit(scull_cleanup_module);
