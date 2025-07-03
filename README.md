# WEEK 1 Tasks overview

# OSI Model concept

1.  Application Layer (Layer 7)==>
        User-facing layer==>
        protocols   HTTP, FTP, DNS
    
3. Presentation Layer (Layer 6)==>
        Responsible for Formatting, encryption, compression
        ==> JPEG, TLS, ASCII
   
4.  Session Layer (Layer 5)==>
        Manages session control
       ==> protocols:
            NetBIOS, SMB
        
6. Transport Layer (Layer 4)==>
        Ensures end-to-end connection==>
        Protocols TCP, UDP
   
7. Network Layer (Layer 3)==>
        Handles routing and IP addressing==>
        Protocols:  IP, ICMP

8. Data Link Layer (Layer 2)==>
        Ensures frame delivery==>
         Ethernet, ARP, PPP
   
9. Physical Layer (Layer 1)==>
        Transmits bits via hardware==>
            Cables, radio, Wi-Fi, signals


# PROGRAMS IMPLEMENTED

# 1. circular buffer(using queue)

# operations
it performs operations such as 
enqueue()
dequeue()
display()

# 2. basic queue

# Basic queue operations:
          enqueue: Add element to the rear
          dequeue: Remove element from the front
          display: Show all current queue elements
   
# 3. linked list(node creation,count,insertion at the end)

# This program includes:

 Creating a static linked list manually
 Counting the number of nodes
 Printing the list data
 Adding a new node at the end dynamically

# Key Functions

count_of_nodes(struct node *head)`
Counts and prints the total number of nodes in the list.

print_data(struct node *head)`
Prints all node data in the list from head to last.

add_at_the_end(struct node *head, int data)`
Adds a new node with the given data at the end of the list.

# 4.state machine

# Message Exchange State Machine

This is a C program that uses a state machine to simulate message exchange between two states.

The FSM transitions between four states:

STATE_IDLE: Waiting to send or receive a message.

STATE_SENDING: Message is being sent.

STATE_WAIT_ACK: Waiting for an acknowledgment after sending.

STATE_RECEIVING: Message has been received and is being processed.

# events:

EVENT_SEND: Send a message.

EVENT_RECEIVE: Receive a message.

EVENT_ACK: Acknowledgment received.

EVENT_TIMEOUT: A timeout occurred while waiting for an ACK.

# output

![Alt Text](recent:///d7902dfd4ab4f206e9d24eb0686676ec)


# C-based UDP Chat App

The application uses sockets to send and receive messages between two devices or processes using User Datagram Protocol (UDP).

Filename:

udp_chat _client

udp_chat_server

The project includes two components:

  Sender: Sends a message to a specific IP and port
  
  Receiver: Listens on a specific port and prints incoming messages

#compilation process:

# Compile udp_chat _client
gcc udp_chat _client.c -o client -pthread

./ client 127.0.0.1 5050

# Compile udp_chat_server

gcc udp_chat_server.c -o server -pthread

./server 5050







