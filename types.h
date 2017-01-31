struct dumb_driver {
	void *dumb_spec_data;
	int (*probe)(struct device *);
	struct device_driver driver;
};

