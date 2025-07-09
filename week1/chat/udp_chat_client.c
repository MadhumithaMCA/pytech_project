// udp_chat_client.c

#include <stdio.h>              // For input/output functions
#include <stdlib.h>             // For atoi() and exit()
#include <string.h>             // For memset(), strlen()
#include <unistd.h>             // For close(), read(), write(), sleep()
#include <pthread.h>            // For using threads
#include <arpa/inet.h>          // For sockaddr_in, inet_addr(), htons()

#define BUF_SIZE 1024           // Define the size of the buffer for messages

// Global variables
struct sockaddr_in serv_addr;   // Server address structure
socklen_t addr_len = sizeof(serv_addr);  // Length of server address
int sockfd;                     // Socket file descriptor (shared between threads)

// Thread function to receive messages from the server
void *receive_messages(void *arg) {
    char buffer[BUF_SIZE];  // Buffer to store received messages

    while (1) {
        // Receive message from server using recvfrom()
        int n = recvfrom(sockfd, buffer, BUF_SIZE, 0,
                         (struct sockaddr *)&serv_addr, &addr_len);

        if (n < 0) {
            perror("Receive failed");
            continue;
        }

        buffer[n] = '\0';  // Null-terminate the received string
        printf("\n[Server]: %s", buffer);  // Display message from server
        fflush(stdout);  // Ensure it prints even if there's no newline
    }

    return NULL;
}

// Thread function to send messages to the server
void *send_messages(void *arg) {
    char buffer[BUF_SIZE];  // Buffer to hold messages typed by the user

    while (1) {
        printf("You: ");
        fgets(buffer, BUF_SIZE, stdin);  // Get user input from stdin

        // Send message to server using sendto()
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&serv_addr, addr_len);
    }

    return NULL;
}

// Main function
int main(int argc, char *argv[]) {
    // Check for required command-line arguments
    if (argc != 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];        // Extract IP address from command line
    int port = atoi(argv[2]);  // Convert port number from string to int

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Set up server address structure
    memset(&serv_addr, 0, sizeof(serv_addr));  // Clear structure
    serv_addr.sin_family = AF_INET;            // IPv4
    serv_addr.sin_port = htons(port);          // Convert port to network byte order
    serv_addr.sin_addr.s_addr = inet_addr(ip); // Convert IP to binary format

    printf(" UDP Client ready. You can start chatting now.\n");

    // Declare thread identifiers
    pthread_t recv_thread, send_thread;

    // Create thread for receiving messages
    if (pthread_create(&recv_thread, NULL, receive_messages, NULL) != 0) {
        perror("Failed to create receive thread");
        return 1;
    }

    // Create thread for sending messages
    if (pthread_create(&send_thread, NULL, send_messages, NULL) != 0) {
        perror("Failed to create send thread");
        return 1;
    }

    // Wait for both threads to finish (they run indefinitely in this case)
    pthread_join(recv_thread, NULL);
    pthread_join(send_thread, NULL);

    // Close the socket before exiting (this line won't be reached unless threads exit)
    close(sockfd);

    return 0;
}




