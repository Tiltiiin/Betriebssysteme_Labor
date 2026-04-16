// pipe.c
// 
// This program demonstrates a simple inter-process communication (IPC)
// between a parent and child process using pipes.
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
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#include <stdio.h>  // Standard input/output library
#include <unistd.h> // POSIX standard library for process control
#include <string.h> // String manipulation library

/**
 * @brief Main function for the pipe demonstration.
 * @return 0 on success, 1 on failure.
 */
int main() {

    // Declaration of variables
    int pipefds[2]; // Array to hold the pipe file descriptors
    pid_t pid; // Process ID
    char write_msg[] = "Hello, child process!"; // Message to be written to the pipe
    char read_msg[100]; // Buffer to read the message from the pipe

    // Create a pipe; pipefds[0] is the read end, pipefds[1] is the write end
    // if pipe() returns -1, an error occurred
    if (pipe(pipefds) == -1) {
        perror("pipe"); // Print an error message
        return 1; // Return 1 to indicate an error
    }

    // Create a child process
    pid = fork();

    // If fork() returns -1, an error occurred
    if (pid == -1) {
        perror("fork"); // Print an error message
        return 1; // Return 1 to indicate an error
    }

    // If pid is 0, the current process is the child process
    if (pid == 0) {
        // Close the write-end of the pipe
        close(pipefds[1]);
        // Read the message from the pipe
        read(pipefds[0], read_msg, sizeof(read_msg));
        printf("\tChild received: %s\n", read_msg);
        // Close the read-end of the pipe
        close(pipefds[0]);
    } else {
        // Parent process
        close(pipefds[0]); // Close the read-end of the pipe to signal EOF
        // Write the message to the pipe
        write(pipefds[1], write_msg, strlen(write_msg) + 1);
        printf("Parent sent: %s\n", write_msg);
        // Close the write-end of the pipe to signal EOF
        close(pipefds[1]);
    }

    return 0;
}