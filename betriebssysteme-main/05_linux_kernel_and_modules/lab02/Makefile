obj-m += mod_syscall_counter.o

KVERSION = $(shell uname -r)

# Default target - build both modules
all:
	$(MAKE) -C /lib/modules/$(KVERSION)/build M=$(PWD) modules

clean:
	$(MAKE) -C /lib/modules/$(KVERSION)/build M=$(PWD) clean

install: all
	$(MAKE) -C /lib/modules/$(KVERSION)/build modules_install
	depmod -a

uninstall:
	rm -f /lib/modules/$(KVERSION)/extra/mod_syscall_counter.ko
	depmod -a

# Help message
help:
	@echo "Makefile for mod_syscall_counter kernel module"
	@echo ""
	@echo "Targets:"
	@echo "  all           - Build all modules (default)"
	@echo "  clean         - Remove all generated files"
	@echo "  install       - Install the modules"
	@echo "  uninstall     - Uninstall the modules"
	@echo ""
	@echo "Architecture is detected automatically"
	@echo ""
	@echo "Note: The compiler warning about differing compilers can usually be ignored" 