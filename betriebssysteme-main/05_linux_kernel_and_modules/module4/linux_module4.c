/*
 * Simple example to show Kernel Module Programming
 * and kernel panic due to wrong kill pid command usage.
 *
 * Author: Rainer Keller, Dennis Grewe, HS Esslingen
 *
 * Compile using:
 *    make modules
 * Load the Kernel module using:
 *    sudo insmod ./linux_module4.ko
 * Remove the module using:
 *    sudo rmmod linux_module4
 * Check the module's output using:
 *    sudo dmesg
 */
#include <linux/kernel.h>   // Für Kernel-Funktionen wie printk
#include <linux/module.h>   // Für Modul-Makros und -Funktionen

MODULE_LICENSE("GPL");  // Gibt die Lizenz des Moduls an (GPL: General Public License)
MODULE_INFO(author, "Rainer Keller, Dennis Grewe");  // Zusatzinfo: Autor des Moduls
MODULE_INFO(intree, "N");  // Zusatzinfo: Gibt an, dass das Modul nicht Teil des Kernbaums ist ("N" für Nein)
MODULE_DESCRIPTION("This module is just for demonstration");  // Kurze Beschreibung des Moduls

// Definiert eine Zeichenkette als Modulparameter mit dem Standardwert "My linux module!"
static char *var = "My linux module!";

// Modulparameter 'var' registrieren
// S_IRUGO gibt die Zugriffsrechte an: Lesezugriff für User, Group und Other
module_param(var, charp, S_IRUGO);
MODULE_PARM_DESC(var, "The variable to pass");  // Beschreibung des Parameters 'var'

// Initialisierungsfunktion des Moduls
// Diese Funktion wird beim Laden des Moduls aufgerufen
__init int my_init_module(void) {
    int *p = 1;  // Fehlerhafter Zeiger: Weist `p` die Adresse `1` zu (ungültig und führt zu Kernel-Absturz)
    
    printk(KERN_DEBUG "Hello %s\n", var);  // Gibt eine Debug-Nachricht im Kernel-Log aus und zeigt den Wert von `var`
    printk(KERN_DEBUG "Killme: %d\n", *p);  // Versucht, den Wert an Adresse `p` zu lesen, was zu einem Fehler führt
    
    return 0;  // Gibt 0 zurück, um anzuzeigen, dass das Modul erfolgreich geladen wurde
}

// Bereinigungsfunktion des Moduls
// Diese Funktion wird beim Entladen des Moduls aufgerufen
__exit void my_cleanup_module(void) {
    // Diese Funktion ist leer, könnte aber verwendet werden, um Ressourcen freizugeben
}

// Makros zur Registrierung der Init- und Exit-Funktionen
module_init(my_init_module);  // Legt fest, dass `my_init_module` beim Laden des Moduls ausgeführt wird
module_exit(my_cleanup_module);  // Legt fest, dass `my_cleanup_module` beim Entladen des Moduls ausgeführt wird