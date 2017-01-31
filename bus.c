#include<linux/init.h>
#include<linux/module.h>
#include<linux/device.h>
#include "types.h"

MODULE_LICENSE("GPL");

static int dumb_bus_probe(struct device *dev)
{
	struct dumb_driver *drv = container_of(dev->driver, struct dumb_driver,
						driver);

	pr_alert("Bus probe called\n");
	pr_alert("Calling dumb specific probe now\n");

	if (drv && drv->probe)
		return drv->probe(dev);

	return -EINVAL;
}

static int dumb_bus_match(struct device *dev, struct device_driver *drv)
{
	pr_alert("Bus match called - Always matches for now\n");

	return 1;
}

struct bus_type dumb_bus_type = {
	.name = "dumb-bus",
	.match = dumb_bus_match,
	.probe = dumb_bus_probe
};
EXPORT_SYMBOL(dumb_bus_type);

int dumb_driver_register(struct dumb_driver *drv)
{
	drv->driver.bus = &dumb_bus_type;
 	return driver_register(&drv->driver);
}
EXPORT_SYMBOL(dumb_driver_register);

void dumb_driver_unregister(struct dumb_driver *drv)
{
	driver_unregister(&drv->driver);
	return;
}
EXPORT_SYMBOL(dumb_driver_unregister);

static int __init dumb_bus_init(void)
{
	return bus_register(&dumb_bus_type);
}

static void __exit dumb_bus_exit(void)
{
	bus_unregister(&dumb_bus_type);
	return;
}

module_init(dumb_bus_init);
module_exit(dumb_bus_exit);

