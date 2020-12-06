#ifndef __DEVICE_H__
#define __DEVICE_H__

typedef int     dev_t;

struct device
{
	const char * name;
	struct file_operations * fops;
};

#define MAX_CHRDEV 32
#define MAX_BLKDEV 32

#endif 

