// udp_chat_server.c
// A simple UDP chat server using threads to handle sending and receiving messages.

#include <stdio.h>              // For standard I/O functions
#include <stdlib.h>             // For atoi(), exit()
#include <string.h>             // For memset(), strlen()
#include <unistd.h>             // For close()
#include <pthread.h>            // For multithreading
#include <arpa/inet.h>          // For socket address functions

#define BUF_SIZE 1024           // Define maximum buffer size for messages

// Global variables
struct sockaddr_in client_addr;          // To store client address info
socklen_t addr_len = sizeof(client_addr);// Length of client address
int sockfd;                              // Socket file descriptor (shared between threads)

// Thread function to receive messages from client
void *receive_messages(void *arg) {
    char buffer[BUF_SIZE]; // Buffer to store incoming messages

    while (1) {
        // Receive message from client
        int n = recvfrom(sockfd, buffer, BUF_SIZE, 0,
                         (struct sockaddr *)&client_addr, &addr_len);

        if (n < 0) {
            perror("Receive failed");
            continue;
        }

        buffer[n] = '\0'; // Null-terminate the received string
        printf("\n[Client]: %s", buffer); // Print received message
        fflush(stdout); // Ensure message is immediately displayed
    }

    return NULL;
}

// Thread function to send messages to client
void *send_messages(void *arg) {
    char buffer[BUF_SIZE]; // Buffer for outgoing messages

    while (1) {
        printf("You: ");
        fgets(buffer, BUF_SIZE, stdin); // Read input from user

        // Send message to client
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&client_addr, addr_len);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    // Check if port number is provided
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]); // Convert port argument from string to integer

    struct sockaddr_in serv_addr; // Server address structure

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Initialize server address struct
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;         // IPv4
    serv_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all network interfaces
    serv_addr.sin_port = htons(port);       // Convert port to network byte order

    // Bind the socket to the address and port
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    printf(" UDP Server ready. Waiting for messages on port %d...\n", port);

    // Declare thread IDs
    pthread_t recv_thread, send_thread;

    // Create thread for receiving messages
    if (pthread_create(&recv_thread, NULL, receive_messages, NULL) != 0) {
        perror("Receive thread creation failed");
        close(sockfd);
        return 1;
    }

    // Create thread for sending messages
    if (pthread_create(&send_thread, NULL, send_messages, NULL) != 0) {
        perror("Send thread creation failed");
        close(sockfd);
        return 1;
    }

    // Wait for threads to finish (they run indefinitely)
    pthread_join(recv_thread, NULL);
    pthread_join(send_thread, NULL);

    // Close the socket before exiting
    close(sockfd);

    return 0;
}


