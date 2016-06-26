obj-m := hello_world.o
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

# M的作用是返回当前目录继续读入makefile
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
#	rm -f *.o *.ko *.mod.c modules* Module*
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
