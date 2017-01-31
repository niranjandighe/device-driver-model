obj-m += bus.o driver.o device.o

all:
	make -C /usr/src/linux-headers-`uname -r`/ M=`pwd` modules
 
clean:
	make -C /usr/src/linux-headers-`uname -r`/ M=`pwd` clean

install:
	sudo rmmod device
	sudo rmmod driver
	sudo rmmod bus
	sudo insmod bus.ko
	sudo insmod driver.ko
	sudo insmod device.ko

