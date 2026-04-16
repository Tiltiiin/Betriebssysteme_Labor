obj-m = linux_module2.o

KVERSION = $(shell uname -r)


modules all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
