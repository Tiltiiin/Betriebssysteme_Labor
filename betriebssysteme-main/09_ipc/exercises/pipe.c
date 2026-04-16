// pipe.c
// 
// This program demonstrates a simple inter-process communication (IPC)
// between a parent and child process using pipes. The program also measures
// the time taken to write to the pipe using the CPU's time-stamp counter (TSC).
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

#include <unistd.h>    // For pipe, fork, read, write, close
#include <stdio.h>     // For printf
#include <stdlib.h>    // For exit
#include <errno.h>     // For errno
#include <string.h>    // For strerror and strlen

#define SIZE 4096      // Buffer size for reading/writing

#define ERROR(s,e) do {                                     \
        fprintf (stderr, "ERROR: %s (strerror of %d:%s)\n", \
                 (s), (e), strerror((e)));                  \
        exit (e);                                           \
    } while(0) // Macro to handle errors

char buffer[SIZE]; // Buffer for reading from the pipe
const char string[] = "Hello56789World56789"; // String to be sent through the pipe

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
    int fd[2]; // File descriptors for the pipe
    int ret; // Return value for system calls

    // Create a pipe
    ret = pipe(fd);
    if (0 != ret)
        ERROR ("pipe()", errno); // Handle pipe creation error

    pid = getpid(); // Get the current process ID

    // Fork the process
    ret = pid_child = fork();
    if (ret == -1)
        ERROR ("fork", errno); // Handle fork error

    if (0 == ret) {
        // CHILD Process: READS from pipe
        int nread = 1; // Number of bytes read
        pid = getpid(); // Get child process ID
        printf ("PID:%d (CHILD)\n", (int)pid);
        close(fd[1]); // Close the write end of the pipe
        while (0 != nread) {
            nread = read(fd[0], buffer, SIZE); // Read from the pipe
            printf ("PID:%d (CHILD) just read:%d Bytes:%s\n", pid, nread, buffer);
        }
    } else if (0 < ret) {
        // PARENT Process: WRITES to pipe
        unsigned long long start; // Start time for performance measurement
        unsigned long long stop; // Stop time for performance measurement
        int ticks; // Time ticks for performance measurement
        int nwrite; // Number of bytes written

        close(fd[0]); // Close the read end of the pipe
        strcpy(buffer, string); // Copy the string to the buffer
        start = getrdtsc(); // Start timing
        nwrite = write(fd[1], buffer, strlen(string)); // Write to the pipe
        stop = getrdtsc(); // Stop timing

        ticks = stop - start; // Calculate elapsed ticks
        printf ("PID:%d time: %d Ticks for %d Bytes\n", pid, ticks, nwrite);
    }

    return 0; // Exit the program
}
