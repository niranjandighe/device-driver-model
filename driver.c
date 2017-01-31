#include<linux/init.h>
#include<linux/module.h>
#include<linux/device.h>
#include "types.h"

extern int dumb_driver_register(struct dumb_driver *drv);
extern void dumb_driver_unregister(struct dumb_driver *drv);

MODULE_LICENSE("GPL");

static int dumb_probe(struct device *dev)
{
	pr_alert("Hello dumb, now probe for further downstream devices here and register them!\n");

	return 0;
}

static struct dumb_driver dumb_driver = {
	.probe = dumb_probe,
	.driver = {
		.name = "dumb-driver",
	}
};

static int __init dumb_driver_init(void)
{
	return dumb_driver_register(&dumb_driver);
}

static void __exit dumb_driver_exit(void)
{
	dumb_driver_unregister(&dumb_driver);
	return;
}

module_init(dumb_driver_init);
module_exit(dumb_driver_exit);

