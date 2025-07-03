#include <stdio.h>

#define SIZE 5  // Define the maximum size of the queue

int queue[SIZE];           // Array to store queue elements
int front = -1, rear = -1; // Indices to track front and rear of the queue

// Function to add an element to the queue
void enqueue(int value) {
    if (rear == SIZE - 1) {
        // Queue is full when rear reaches the last index
        printf("Queue is full\n");
    } else {
        if (front == -1) front = 0; // Initialize front on first enqueue
        rear++;                     // Move rear to the next position
        queue[rear] = value;        // Insert the value
        printf("%d enqueued\n", value);
    }
}

// Function to remove an element from the queue
void dequeue() {
    // Check if queue is empty
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
    } else {
        printf("%d dequeued\n", queue[front]); // Remove front element
        front++; // Move front to the next element
    }
}

// Function to display all elements of the queue
void display() {
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
    } else {
        printf("Queue: ");
        for (int i = front; i <= rear; i++) {
            printf("%d ", queue[i]); // Print each element from front to rear
        }
        printf("\n");
    }
}

int main() {
    enqueue(2);  // Add 2 to the queue
    enqueue(3);  // Add 3 to the queue
    enqueue(5);  // Add 5 to the queue

    display();   // Show current queue contents

    dequeue();   // Remove the front element (2)

    display();   // Show updated queue contents

    return 0;
}

