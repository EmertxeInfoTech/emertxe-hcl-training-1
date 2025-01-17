# If called directly from the command line, invoke the kernel build system.
ifeq ($(KERNELRELEASE),)

	#KERNEL_SOURCE := /usr/src/linux-headers-$(shell uname -r)
	KERNEL_SOURCE := /home/mentor1/Yocto/Sources/tmp/work/qemux86_64-poky-linux/linux-yocto/6.6.54+git/linux-qemux86_64-standard-build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNEL_SOURCE) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_SOURCE) M=$(PWD) clean

# Otherwise KERNELRELEASE is defined; we've been invoked from the
# kernel build system and can use its language.
else

	obj-m := dummy.o
	obj-m := virtio_net.o

endif
