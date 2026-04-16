// memory_allocation.c
// 
// This program demonstrates dynamic memory allocation and reallocation in C.
// It allocates an initial block of memory, then continuously reallocates
// larger blocks while optionally zeroing out the memory. The program sleeps
// for a specified duration between reallocations to simulate a long-running
// process.
//
// Author: Rainer Keller, Dennis Grewe
// Date: 10.11.2024
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE_START 4096  // Initial size of the memory block
#define SIZE_DELTA 4096  // Increment size for each reallocation
#define SLEEP_MS   (1000*1000)  // Sleep duration in microseconds
#define MEMSET  // Define to enable memory zeroing
#define MEMSET_CHAR '\0'  // Character used for memset

/**
 * @brief Main function for the memory allocation demonstration.
 *
 * This function allocates an initial block of memory, then enters a loop
 * where it reallocates larger blocks of memory while optionally zeroing
 * out the memory. The program prints the pointer and size of the allocated
 * memory block after each reallocation.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return int Exit status of the program.
 */
int main (int argc, char * argv[])
{
    char * p;  // Pointer to the allocated memory
    size_t size = SIZE_START;  // Current size of the allocated memory

    // Allocate initial memory block
    p = malloc(size);
    if (NULL == p)  // Check for successful allocation
        goto fail;

    // Loop to continuously reallocate memory
    while (NULL != p) {
        usleep(SLEEP_MS);  // Sleep for a specified duration
#if defined(MEMSET)
        memset(p, MEMSET_CHAR, size);  // Zero out the allocated memory
#endif
        size += SIZE_DELTA;  // Increase the size for the next allocation
        p = realloc(p, size);  // Reallocate memory

        // Print the pointer and size of the allocated memory
        printf("p:%p size:%zu\n", (void *)p, size);
    }

fail:
    free(p);  // Free the allocated memory before exiting
    return 0;  // Exit the program
}
