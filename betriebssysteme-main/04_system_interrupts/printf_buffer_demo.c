/*  buffer_demo.c
 *
 *  Demonstriert, dass printf() erst beim Zeilenumbruch (\n)
 *  oder fflush() einen write-Syscall auslöst.
 *
 *  Kompilieren:  gcc -Wall -O0 printf_buffer_demo.c -o buffer_demo
 *  Ausführen:    strace -e write ./buffer_demo
 */

#define _GNU_SOURCE     /* für STDOUT_FILENO */
#include <unistd.h>     /* write, STDOUT_FILENO */
#include <stdio.h>      /* printf, fflush */
#include <string.h>     /* strlen */
#include <time.h>       /* nanosleep */

static void wait_sec(int sec)
{
    struct timespec ts = { .tv_sec = sec, .tv_nsec = 0 };
    nanosleep(&ts, NULL);
}

int main(void)
{
    /* 1) Gepufferte Ausgabe ohne \n  (bleibt in libc-Puffer) */
    printf("A) printf ohne Newline ...");
    wait_sec(2);                     /* <-- Noch kein write() sichtbar   */

    /* 2) Jetzt Newline  →  libc flush → 1× write() */
    printf("  jetzt mit Newline!\n");
    wait_sec(2);                     /* <-- write() bereits passiert     */

    /* 3) Wieder ohne Newline, aber manuelles fflush() */
    printf("B) printf ohne Newline, manuelles fflush");
    fflush(stdout);                  /* <-- sofortiger write()           */
    wait_sec(2);

    /* 4) Ungepufferter direkter System-Call */
    const char *msg = "C) ungepufferter write()\n";
    write(STDOUT_FILENO, msg, strlen(msg));   /* <-- sofortiger write() */
    return 0;
}