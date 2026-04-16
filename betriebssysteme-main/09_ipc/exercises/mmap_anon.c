// mmap_anon.c
// 
// This program demonstrates the use of anonymous memory mapping with fork.
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

#include <sys/types.h>  // For data types
#include <sys/mman.h>   // For mmap
#include <err.h>        // For error handling
#include <errno.h>      // For errno
#include <fcntl.h>      // For file control options
#include <stdio.h>      // For printf
#include <stdlib.h>     // For exit and malloc
#include <string.h>     // For strcpy
#include <unistd.h>     // For fork, getpid, sleep

#define ERROR(s,e) do {                                     \
        fprintf (stderr, "ERROR: %s (strerror of %d:%s)\n", \
                 (s), (e), strerror((e)));                  \
        exit (e);                                           \
    } while(0) // Macro for error handling

/**
 * @brief Demonstrates the use of anonymous memory mapping with fork.
 * 
 * This program creates an anonymous memory mapping using mmap, 
 * allowing both the parent and child processes to share the same 
 * memory space. The parent process writes a string to the mapped 
 * memory, and the child process reads from it, demonstrating 
 * inter-process communication through shared memory.
 * 
 * @param argc Argument count
 * @param argv Argument vector
 * @return EXIT_SUCCESS on success, or an error code on failure.
 */
int main(int argc, char * argv[])
{
    const char str1[] = "string 1"; // Initial string for parent
    const char str2[] = "string 2"; // String to overwrite in parent
    int parpid = getpid(), childpid; // Store parent PID
    char *anon; // Pointer for the anonymous memory mapping

    // Create an anonymous memory mapping
    anon = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);
    if (anon == MAP_FAILED) // Check for mmap failure
        ERROR("mmap anon", errno);

    // Copy the initial string to the mapped memory
    strcpy(anon, str1);

    // Fork the process
    switch ((childpid = fork())) {
    case -1:
        ERROR("fork", errno); // Handle fork error

    case 0: // Child process
        childpid = getpid(); // Get child PID
        printf("PID %d (CHILD):\tanonymous %s\n", childpid, anon); // Read initial string
        sleep(3); // Sleep to allow parent to modify the string

        // Read the modified string after parent writes
        printf("PID %d (CHILD):\tanonymous %s\n", childpid, anon);
        return (EXIT_SUCCESS); // Exit child process
    }

    // Parent process
    sleep(2); // Sleep to allow child to read initial string
    strcpy(anon, str2); // Modify the string in shared memory

    // Print the modified string from the parent
    printf("PID %d:\tanonymous %s\n", parpid, anon);
    return (EXIT_SUCCESS); // Exit parent process
}