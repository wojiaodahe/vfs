#include "fs.h"
#include "error.h"
#include "device.h"
#include <stdio.h>

#define MAX_CHRDEV 32
#define MAX_BLKDEV 32


static struct device chrdevs[MAX_CHRDEV] = 
{
	{ NULL, NULL },
};

struct file_operations * get_chrfops(unsigned int major)
{
	if (major >= MAX_CHRDEV)
		return NULL;
	return chrdevs[major].fops;
}

int register_chrdev(unsigned int major, const char * name, struct file_operations *fops)
{
	if (major >= MAX_CHRDEV)
		return -EINVAL;
	if (chrdevs[major].fops)
		return -EBUSY;
	chrdevs[major].name = name;
	chrdevs[major].fops = fops;

	return 0;
}



int chrdev_open(struct inode *inode, struct file *filp)
{
	int i;

	i = MAJOR(inode->i_rdev);
	if (i >= MAX_CHRDEV || !chrdevs[i].fops)
		return -ENODEV;
	filp->f_op = chrdevs[i].fops;
	if (filp->f_op->open)
		return filp->f_op->open(inode,filp);
	return 0;

}

struct file_operations def_chr_fops = 
{
	chrdev_open,	/* open */
	NULL,		    /* close */
	NULL,		    /* read */
	NULL,		    /* write */
	NULL,	    	/* ioctl */
	NULL,	    	/* lseek */
	NULL,		    /* readdir */
};

struct inode_operations chrdev_inode_operations = 
{
	&def_chr_fops,		/* default file operations */
	NULL,			/* create */
	NULL,			/* lookup */
	NULL,			/* mkdir */
	NULL,			/* rmdir */
	NULL,			/* mknod */
	NULL,			/* rename */
};

