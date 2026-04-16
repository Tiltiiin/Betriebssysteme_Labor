/*
 * Simple example to show Kernel Module Programming
 *
 * Author: Rainer Keller, Dennis Grewe, HS Esslingen
 *
 * Compile using:
 *    make modules
 * Load the Kernel module using:
 *    sudo insmod ./linux_module3.ko
 * Remove the module using:
 *    sudo rmmod linux_module3
 * Check the module's output using:
 *    sudo dmesg
 */
#include <linux/kernel.h>   // Für Kernel-Funktionen wie printk
#include <linux/module.h>   // Für Modul-Makros und -Funktionen

/* Modulinformationen bereitstellen */
MODULE_LICENSE("GPL");  // Gibt die Lizenz des Moduls an (GPL: General Public License)
MODULE_INFO(author,"Rainer Keller, Dennis Grewe");  // Zusatzinfo: Autor des Moduls
MODULE_INFO(intree, "N");  // Zusatzinfo: Dieses Modul ist nicht Teil des Kernbaums ("N" für Nein)
MODULE_DESCRIPTION("This module is just for demonstration");  // Beschreibung des Moduls

// Definiert eine Zeichenkette als Modulparameter mit dem Standardwert "My linux module!"
static char *var = "My linux module!";

// Modulparameter 'var' registrieren
// S_IRUGO gibt die Zugriffsrechte an: Lesezugriff für User, Group und Other
module_param(var, charp, S_IRUGO);
MODULE_PARM_DESC(var, "The variable to pass");  // Beschreibung des Parameters 'var'

// Funktion, die beim Laden des Moduls aufgerufen wird
__init int my_init_module(void) {
  // Gibt beim Laden des Moduls eine Debug-Nachricht aus, die den Inhalt von 'var' ausgibt
  printk(KERN_DEBUG "Hello %s\n", var);
  return 0;  // Gibt 0 zurück, um anzuzeigen, dass das Modul erfolgreich geladen wurde
}

// Funktion, die beim Entladen des Moduls aufgerufen wird
__exit void my_cleanup_module(void) {
  // Diese Funktion ist leer, könnte aber verwendet werden, um Ressourcen freizugeben
}

// Makros zur Registrierung der Init- und Exit-Funktionen
module_init(my_init_module);  // Legt fest, dass 'my_init_module' beim Laden des Moduls ausgeführt wird
module_exit(my_cleanup_module);  // Legt fest, dass 'my_cleanup_module' beim Entladen des Moduls ausgeführt wird