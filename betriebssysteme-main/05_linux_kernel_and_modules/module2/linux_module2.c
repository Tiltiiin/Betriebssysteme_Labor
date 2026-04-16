/*
 * Simple example to show Kernel Module Programming
 *
 * Author: Rainer Keller, Dennis Grewe, HS Esslingen
 *
 * Compile using:
 *    make modules
 * Load the Kernel module using:
 *    sudo insmod ./linux_module2.ko
 * Remove the module using:
 *    sudo rmmod linux_module2
 * Check the module's output using:
 *    sudo dmesg
 */

// C-Preprocessor directives
#include <linux/kernel.h>
#include <linux/module.h>

/* Modulinformationen bereitstellen */
MODULE_LICENSE("GPL");  // Gibt die Lizenz des Moduls an (GPL: General Public License)
MODULE_INFO(author,"Rainer Keller, Dennis Grewe");  // Zusatzinfo: Autor des Moduls
MODULE_INFO(intree, "N");  // Zusatzinfo: Dieses Modul ist nicht Teil des Kernbaums ("N" für Nein)
MODULE_DESCRIPTION("This module is just for demonstration");  // Beschreibung des Moduls

/* Init wird beim Laden des Moduls gerufen */
__init int my_init_module(void) {
  printk(KERN_DEBUG "Hello BS Course from linux_module.\n");
  return 0;
}

/* Exit wird beim Entladen des Moduls gerufen */
__exit void my_cleanup_module(void)
{ }

/* Macros beruecksichtigen*/
module_init(my_init_module);
module_exit(my_cleanup_module);
