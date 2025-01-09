# If called directly from the command line, invoke the kernel build system.
SRC_FILES := $(wildcard *.c)
OBJ_FILES := $(patsubst %.c,%.o,$(SRC_FILES))


KERNEL_SOURCE := /usr/src/linux-headers-`uname -r`
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNEL_SOURCE) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_SOURCE) M=$(PWD) clean

# Otherwise KERNELRELEASE is defined; we've been invoked from the
# kernel build system and can use its language.
#obj-m := $(patsubst %.c,%.o,$(wildcard *.c))
obj-m += $(patsubst %.c,%.o,$(SRC_FILES))

#obj-m += final_char_driver.o first_char_driver.o mem_ioctl.o
