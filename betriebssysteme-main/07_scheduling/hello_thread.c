/**
 * Beispiel für die Erstellung eines Threads mit der Pthreads-Bibliothek:
 * 
 * pthread_create wird verwendet, um einen neuen Thread zu erstellen.
 * pthread_join wird verwendet, um auf den Abschluss eines Threads zu warten.
 *
 * Copyright 2024, Dennis Grewe, HS Esslingen
 * Compile:
 *      gcc -Wall -o2 -o hello_thread hello_thread.c
 */
#include <pthread.h>
#include <stdio.h>

void *thread_function(void *arg) {
    printf("Hello from the thread!\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);
    pthread_join(thread, NULL);
    return 0;
}