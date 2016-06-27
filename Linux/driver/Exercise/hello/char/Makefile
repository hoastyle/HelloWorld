#ifneq ($(KERNELRELEASE),)
#obj-m := hello_world.o
#else
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

# M的作用是返回当前目录继续读入makefile
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

help:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) help

clean:
#	rm -f *.o *.ko *.mod.c modules* Module*
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
#endif
