# bulid the kernel module for rpi arm64

export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-

obj-m += \
	src/gpio_drv.o

EXTRA_CFLAGS=-I$(PWD)/inc

ifneq ($(ARCH), arm64)
	KDIR = /lib/modules/$(shell uname -r)/build
endif

KDIR = /home/venu/projects/linux

all:
	make -C $(KDIR)  M=$(shell pwd) modules

clean:
	make -C $(KDIR)  M=$(shell pwd) clean