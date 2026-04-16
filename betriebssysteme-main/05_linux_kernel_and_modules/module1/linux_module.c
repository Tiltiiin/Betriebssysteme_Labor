/*
 * Simple example to show Kernel Module Programming
 *
 * Author: Rainer Keller, Dennis Grewe, HS Esslingen
 *
 * Compile using:
 *    make modules
 * Load the Kernel module using:
 *    sudo insmod ./linux_module.ko
 * Remove the module using:
 *    sudo rmmod linux_module
 * Check the module's output using:
 *    sudo dmesg
 */
#include <linux/kernel.h>  // For kernel log macros like printk
#include <linux/module.h>  // For module-related macros and functions

MODULE_LICENSE("GPL");  // Specifies the license, necessary for legal and functionality reasons in kernel modules

// The `init_module` function is supposed to be the module's entry point.
__init int init_module(void) {
  printk(KERN_DEBUG "Hello\n");  // Logs "Hello" at the debug level in the kernel log
  return 0;  // Returns 0 to indicate successful loading
}

// The `cleanup_module` function is supposed to be the module's exit function.
__exit void cleanup_module(void) {}

// maybe the following macros required:
//module_init(my_init_module);
//module_exit(my_cleanup_module);

