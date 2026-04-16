// signals.c
// This program demonstrates how to handle signals in a program.
// It creates a child process and sends a signal to it.
// The child process then handles the signal and prints a message.
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
#include <unistd.h> // POSIX standard library for process control
#include <signal.h> // Signal library

/**
 * @brief Signal handler function.
 * @param signum The signal number.
 */
void signal_handler(int signum) {
    printf("Signal %d received\n", signum);
}

/**
 * @brief Main function for the signal demonstration.
 * @return 0 on success, 1 on failure.
 */
int main() {
    // register the signal handler
    // SIGINT is the signal number for the interrupt signal (Ctrl+C)
    signal(SIGINT, signal_handler);

    if (fork() == 0) {
        // child process
        sleep(2); // sleep for 2 seconds
        kill(getppid(), SIGINT); // send SIGINT signal to the parent process
    } else {
        // parent process
        printf("Parent waiting for signal...\n"); // print the waiting message
        pause(); // wait for a signal
    }

    return 0; // return 0 on success
}