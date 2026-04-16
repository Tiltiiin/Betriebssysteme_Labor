// named_pipes.c
// 
// This program demonstrates the use of named pipes (FIFOs) for inter-process communication.
// It creates a named pipe, forks a child process, and communicates between the parent and child using the named pipe.
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

#include <stdio.h>  // Standard input/output library
#include <stdlib.h> // Standard library
#include <string.h> // String manipulation library
#include <unistd.h> // POSIX standard library for process control
#include <sys/stat.h>  // File status definitions
#include <fcntl.h>     // File control definitions

#define FIFO_NAME "/tmp/my_fifo" // Define the named pipe file path

/**
 * @brief Main function for the named pipe demonstration.
 * @return 0 on success, 1 on failure.
 */
int main() {
    // Declaration of variables
    int fd; // File descriptor
    char write_msg[] = "Message through FIFO"; // Message to be written to the FIFO
    char read_msg[100]; // Buffer to read the message from the FIFO

    // Create the named pipe (FIFO) with specified permissions
    // 0666 means; 0 = octal indicator, 6 = user permissions, 6 = group permissions, 6 = other permissions
    // 0666 = rw-rw-rw-
    mkfifo(FIFO_NAME, 0666);

    // Create a child process
    if (fork() == 0) {
        // Child process (Reader)
        fd = open(FIFO_NAME, O_RDONLY); // Open the FIFO for reading
        read(fd, read_msg, sizeof(read_msg)); // Read the message from the FIFO
        printf("\tChild received: %s\n", read_msg); // Print the received message
        close(fd); // Close the FIFO
        unlink(FIFO_NAME); // Remove the FIFO
    } else {
        // Parent process (Writer)
        fd = open(FIFO_NAME, O_WRONLY);
        write(fd, write_msg, strlen(write_msg) + 1); // Write the message to the FIFO
        printf("Parent sent: %s\n", write_msg); // Print the sent message
        close(fd); // Close the FIFO
    }

    return 0;
}