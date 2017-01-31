#include<linux/init.h>
#include<linux/module.h>
#include<linux/device.h>
#include<linux/slab.h>
#include "types.h"

MODULE_LICENSE("GPL");

extern struct bus_type dumb_bus_type;

static struct device *dev; 

void dumb_release(struct device *dev)
{
}

static int __init dumb_device_init(void)
{
	dev = kzalloc(sizeof(struct device), GFP_KERNEL);
	if (dev) {
		dev->bus = &dumb_bus_type;
		dev->release = dumb_release;
		dev_set_name(dev, "%s", "dumb-device");

		return device_register(dev);
	}

	return -ENOMEM;
}

static void __exit dumb_device_exit(void)
{
	device_unregister(dev);
	kfree(dev);

	return;
}

module_init(dumb_device_init);
module_exit(dumb_device_exit);

