// shared_mem.c
// This program demonstrates shared memory between a parent and child process.
// Author: Dennis Grewe
// Date: 16.11.2024
// 
// This program is free to use for educational purposes but is not allowed
// to be shared outside the course "Betriebsysteme" at Esslingen University.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

#include <stdio.h>  // Standard input/output library
#include <stdlib.h> // Standard library
#include <string.h> // String manipulation library
#include <unistd.h> // POSIX standard library for process control
#include <sys/shm.h> // System shared memory library
#include <sys/types.h> // System type definitions
#include <sys/ipc.h> // System IPC library

/**
 * @brief Main function for the shared memory demonstration.
 * @return 0 on success, 1 on failure.
 */
int main() {
    // Declaration of variables
    int shmid; // Shared memory identifier
    key_t key; // Key for the shared memory
    char *shmaddr; // Pointer to the shared memory

    // Generate unique key
    // "shmfile" is the path to the shared memory file
    // 65 is the project identifier - can be any number to identify the project
    key = ftok("shmfile", 65);

    // Create shared memory segment
    // 1024 is the size of the shared memory segment
    // 0666 is the permissions for the shared memory segment
    // IPC_CREAT is the flag to create the shared memory segment if it doesn't exist
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // Attach the shared memory segment to the address space of the calling process
    shmaddr = (char *)shmat(shmid, NULL, 0);

    // Create a child process
    if (fork() == 0) {
        // Child process (Reader)
        strcpy(shmaddr, "Hello from child process!"); // Copy the message to the shared memory
        printf("\tChild wrote: %s\n", shmaddr); // Print the written message
        shmdt(shmaddr); // Detach the shared memory segment
    } else {
        // Parent process (Writer)
        strcpy(shmaddr, "Hello from parent process!"); // Copy the message to the shared memory
        printf("Parent wrote: %s\n", shmaddr); // Print the written message
        shmdt(shmaddr); // Detach the shared memory segment
        wait(NULL); // Wait for the child process to finish
        shmctl(shmid, IPC_RMID, NULL); // Destroy the shared memory segment
    }

    return 0;
}