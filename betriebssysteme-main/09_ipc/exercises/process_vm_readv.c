// process_vm_readv.c
// 
// This program demonstrates the use of process_vm_readv and process_vm_writev
// to read and write to another process' memory. Program only works on Linux.
//
// Author: Rainer Keller, Dennis Grewe
// Date: 16.11.2024
//
// This program is free to use for educational purposes but is not allowed
// to be shared outside the course "Betriebsysteme" at Esslingen University.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#define _GNU_SOURCE // Enable GNU extensions

#include <stdio.h>      // For printf
#include <stdlib.h>     // For exit and malloc
#include <string.h>     // For memset and strerror
#include <unistd.h>     // For fork, getpid, sleep
#include <errno.h>      // For errno
#include <sys/uio.h>    // For struct iovec and process_vm_readv/writev

#define SIZE 4096       // Size of the buffer
#define PROCS 2         // Number of processes

#define ERROR(s,e) do {                                     \
        fprintf (stderr, "ERROR: %s (strerror of %d:%s)\n", \
                 (s), (e), strerror((e)));                  \
        exit (e);                                           \
    } while(0) // Macro for error handling

#define SLEEP_MS   (1000*1000) // Sleep duration in microseconds
#define MEMSET // Define to enable buffer initialization
#define MEMSET_CHAR '\0' // Character to initialize buffer

/* Local variable definitions */
static char buffer[PROCS * SIZE]; // Shared buffer for inter-process communication

/**
 * @brief Reads the time-stamp counter (TSC) to measure performance.
 * 
 * This function uses inline assembly to read the CPU's time-stamp counter,
 * which provides a high-resolution timer for performance measurement.
 * 
 * @return The current value of the time-stamp counter.
 */
static unsigned long long int getrdtsc(void)
{
    unsigned int hi, lo;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi)); // Read TSC
    return (((unsigned long long int)hi << 32) | ((unsigned long long int)lo));
}

int main (int argc, char * argv[])
{
    pid_t pid; // Process ID
    pid_t pid_child; // Child process ID
    unsigned long long start; // Start time for performance measurement
    unsigned long long stop; // Stop time for performance measurement
    int ret; // Return value for system calls

#if defined(MEMSET)
    memset (buffer, MEMSET_CHAR, SIZE); // Initialize buffer
#endif

    pid = getpid(); // Get the current process ID

    // Fork the process
    ret = pid_child = fork();
    if (ret == -1)
        ERROR ("fork", errno); // Handle fork error

    if (0 == ret) {
        /* CHILD Process */
        pid = getpid(); // Get child process ID
        printf ("PID:%d (CHILD) buffer:%s\n", (int)pid, buffer); // Print initial buffer
        sleep (2); // Sleep to allow parent to write to the buffer

        // Print the buffer after the parent has written to it
        printf ("PID:%d (CHILD) NOW buffer:%s\n", pid, buffer);
        
    } else if (0 < ret) {
        // PARENT Process
        struct iovec local[2]; // Local buffers for writing
        struct iovec remote[1]; // Remote buffer for reading
        char buf1[10] = "Hello56789"; // First message to write
        char buf2[10] = "World56789"; // Second message to write
        ssize_t nwrite; // Number of bytes written
        int ticks; // Time ticks for performance measurement

        // Set up local and remote iovec structures
        local[0].iov_base = buf1; // First local buffer
        local[0].iov_len = 10; // Length of first buffer
        local[1].iov_base = buf2; // Second local buffer
        local[1].iov_len = 10; // Length of second buffer
        remote[0].iov_base = (void *) buffer; // Remote buffer
        remote[0].iov_len = 20; // Total length to write

        sleep (1); // Sleep to allow child to print initial buffer

        // Measure the time taken to write to the child's memory
        start = getrdtsc(); // Start timing
        nwrite = process_vm_writev(pid_child, local, 2, remote, 1, 0); // Write to child's memory
        stop = getrdtsc(); // Stop timing

        ticks = stop - start; // Calculate elapsed ticks
        printf ("PID:%d time: %d Ticks for %ld Bytes\n", pid, ticks, nwrite); // Print timing results

        // Check if the number of bytes written is correct
        if (nwrite != 20) {
            char error[32];
            snprintf (error, sizeof(error), "nwrite:%ld != 20\n", nwrite);
            ERROR(error, EINVAL); // Handle write error
        }
        sleep (1); // Sleep before exiting
    }

    return 0; // Exit the program
}