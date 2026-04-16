// sockets_local.c
// This program demonstrates a simple inter-process communication (IPC)
// between a parent and child process using sockets.
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
#include <sys/socket.h> // System socket library
#include <sys/un.h> // System UNIX domain socket library

#define SOCKET_NAME "/tmp/socket_local" // Define the socket path
#define BUFFER_SIZE 128 // Define the buffer size

/**
 * @brief Main function for the socket demonstration.
 * @return 0 on success, 1 on failure.
 */
int main() {
    // Declaration of variables
    int sockfd; // Socket file descriptor
    struct sockaddr_un server_addr; // Server address
    struct sockaddr_un client_addr; // Client address
    char buffer[BUFFER_SIZE]; // Buffer for the message
    int bytes_received; // Number of bytes received

    // Create a child process
    if (fork() == 0) {
        // Child process (Client)
        sleep(1); // Sleep for 1 second to ensure the server is ready
        printf("Child waiting for server...\n"); // Print the waiting message
        sockfd = socket(AF_UNIX, SOCK_STREAM, 0); // Create the socket
        client_addr.sun_family = AF_UNIX; // Set the family to UNIX
        strncpy(client_addr.sun_path, SOCKET_NAME, sizeof(client_addr.sun_path) - 1); // Copy the socket path to the client address
        connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)); // Connect to the server
        write(sockfd, "Hello from client!", 19); // Write the message to the server
        printf("Child sent: Hello from client!\n"); // Print the sent message
        close(sockfd); // Close the socket (cleanup)
    } else {
        // Parent process (Server)
        int connfd; // Connection file descriptor
        sockfd = socket(AF_UNIX, SOCK_STREAM, 0); // Create the socket
        server_addr.sun_family = AF_UNIX; // Set the family to UNIX
        strncpy(server_addr.sun_path, SOCKET_NAME, sizeof(server_addr.sun_path) - 1); // Copy the socket path to the server address
        bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)); // Bind the socket to the server address
        listen(sockfd, 5); // Listen for connections
        connfd = accept(sockfd, (struct sockaddr *)NULL, NULL); // Accept a connection
        bytes_received = read(connfd, buffer, BUFFER_SIZE); // Read the message from the client
        printf("Server received: %s\n", buffer); // Print the received message 
        close(connfd); // Close the connection (cleanup)
        close(sockfd); // Close the socket (cleanup)
        unlink(SOCKET_NAME); // Remove the socket file (cleanup)
    }
}