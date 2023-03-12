ifneq ($(KERNELRELEASE),)
# # call from kernel build system

obj-m	:= hello.o

else

KERNELDIR ?= /lib/modules/2.6.10/build
PWD       := $(shell pwd)

default:
 	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif