// message_queue.c
// 
// This program demonstrates the use of message queues for inter-process communication.
// It creates a message queue, forks a child process, and communicates between the parent and child using the message queue.
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

#include <stdio.h> // Standard input/output library
#include <sys/ipc.h> // System IPC library
#include <sys/msg.h> // System message queue library
#include <string.h> // String manipulation library
#include <unistd.h> // Include for fork and other POSIX functions

#define MAX 100 // Define the maximum message length

/**
 * @brief Structure for message queue
 */
struct message {
    long msg_type; // Message type
    char msg_text[MAX]; // Message text
};

/**
 * @brief Main function for the message queue demonstration.
 * @return 0 on success, 1 on failure.
 */
int main() {
    // Declaration of variables
    key_t key; // Key for the message queue
    int msgid; // Message queue identifier

    // Generate unique key
    // "progfile" is the path to the program file
    // 65 is the project identifier - can be any number to identify the project
    key = ftok("progfile", 65);

    // Create a message queue and return identifier
    // 0666 is the permissions for the message queue
    // 0 = octal indicator, 6 = user permissions, 6 = group permissions, 6 = other permissions
    // IPC_CREAT is the flag to create the message queue if it doesn't exist
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Create a child process
    if (fork() == 0) {
        // Child process (Receiver)
        struct message msg;
        msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0); // Receive the message
        printf("\tChild received: %s\n", msg.msg_text); // Print the received message
        msgctl(msgid, IPC_RMID, NULL); // Destroy the message queue
    } else {
        // Parent process (Sender)
        struct message msg;
        msg.msg_type = 1; // Message type
        strcpy(msg.msg_text, "Hello from message queue!"); // Copy the message to the message queue
        msgsnd(msgid, &msg, sizeof(msg.msg_text), 0); // Send the message
        printf("Parent sent: %s\n", msg.msg_text); // Print the sent message
    }

    return 0;
}