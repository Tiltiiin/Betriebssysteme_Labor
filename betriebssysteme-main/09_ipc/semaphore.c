// semaphore.c
// This program demonstrates how to use semaphores to synchronize access to a shared resource.
// It creates a child process and sends a signal to it.
//
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

#include <stdio.h>      // Standard input/output library
#include <stdlib.h>     // Standard library
#include <pthread.h>    // POSIX thread library
#include <semaphore.h>   // Semaphore library
#include <fcntl.h>      // For O_* constants
#include <sys/stat.h>   // For mode constants
#include <unistd.h>     // POSIX standard library for process control

#define NUM_THREADS 5   // Number of threads
#define INCREMENTS 1000  // Number of increments per thread

// Shared resource
int counter = 0;

// Semaphore name
const char* semaphore_name = "/my_semaphore"; // Name for the semaphore

/**
 * @brief Function to increment the shared counter.
 * @param arg Pointer to thread number (not used).
 */
void* increment_counter(void* arg) {
    // Get the semaphore pointer from the argument
    sem_t* semaphore = (sem_t*)arg;

    for (int i = 0; i < INCREMENTS; i++) {
        // Wait (decrement) the semaphore
        sem_wait(semaphore);
        
        // Critical section
        counter++;
        
        // Signal (increment) the semaphore
        sem_post(semaphore);
    }
    return NULL;
}

/**
 * @brief Main function to demonstrate semaphore usage.
 * @return 0 on success.
 */
int main() {
    pthread_t threads[NUM_THREADS];

    // Create the semaphore
    sem_t* semaphore = sem_open(semaphore_name, O_CREAT, 0644, 1);
    if (semaphore == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, (void*)semaphore);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Close the semaphore
    sem_close(semaphore);
    sem_unlink(semaphore_name); // Remove the semaphore from the system

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);
    return 0; // Return 0 on success
}