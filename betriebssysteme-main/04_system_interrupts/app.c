/*
 * Programm um C Programmierkonzepte zu erklären
 *
 * Author: Rainer Keller, HS Esslingen
 * Author: Dennis Grewe, HS Esslingen
 * 
 * Übersetzen mit:
 *    gcc -Wall -O2 -o app app.c
 */
#include <stdio.h>                    // für Ausgabe von Inhalte auf Konsole
#include <stdlib.h>                   // für dyn. Speicherbereitstellung, z.B.: malloc()
#include <sys/types.h>                // stellt OS-unabhängige Datentyen dar, z.B: pid_t für Prozessid
#include <unistd.h>                   // stellt UNIX/POSIX systemen Zugriff auf Betriebssystemfkt bereit
                                      // z.B.: getpid() um aktuelle Prozessid vom BS Kernel zu lesen.

//static int myvar=0;                 // Initialiisierte globale Variable
static int mama=42;                   // Initialiisierte globale Variable

void myfunc(void) {                   // Fkt, die eine globale Variable überschreibt
    mama=4711;
}

int main (int argc, char* argv[]){
    myfunc();                         // Aufruf der Funktion
    char * mem = malloc(1024);        // Memory Allocation
    printf("mama:%d mem:%p pid:%d\n", // Ausgabe der Werte...
           mama, mem, (int)getpid()); // mittels syscall aktuelle ProzessID lesen
    return EXIT_SUCCESS;              // Programm beenden
    // ACHTUNG: free(mem) fehlt ,-)))
}
