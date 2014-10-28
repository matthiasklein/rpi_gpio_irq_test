PWD		:= $(shell pwd)

CC		:= ${CROSS_COMPILE}gcc -Wall -Wno-unused-function

ifeq ($(KERNELRELEASE),)
all:
	$(MAKE) V=0 -C $(KDIR) SUBDIRS=$(PWD) modules
else
	obj-m	:= irq_test_driver.o
	irq_test_driver-objs := irq_test.o
endif

clean:
	-rm -f *.o *.ko modules.order Module.symvers *.mod.c .*.cmd
	-rm -rf .tmp_versions

upload:
	-ssh 192.9.200.1 -i /bsp/ssh/ssh-rpi-ptxdist -o "StrictHostKeyChecking no" -l root rmmod irq_test_driver.ko
	scp -i /bsp/ssh/ssh-rpi-ptxdist -o "StrictHostKeyChecking no" irq_test_driver.ko root@192.9.200.1:/tmp/
