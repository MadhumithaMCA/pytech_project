#include <stdio.h>
#include <stdbool.h>

#define SIZE 5  // Define the maximum size of the circular buffer

// Global buffer array, head and tail pointers, and a count for tracking elements
int buffer[SIZE];
int head = 0;     // Points to the front (element to be dequeued)
int tail = 0;     // Points to the next empty position (for enqueue)
int count = 0;    // Tracks the number of elements currently in the buffer

// Function to check if the buffer is full
bool is_full() {
    return count == SIZE;
}

// Function to check if the buffer is empty
bool is_empty() {
    return count == 0;
}

// Function to add an element to the buffer
void enqueue(int value) {
    if (is_full()) {
        // Cannot add more elements if buffer is full
        printf("Buffer is full. Cannot enqueue %d\n", value);
        return;
    }
    buffer[tail] = value;                   // Insert at tail
    tail = (tail + 1) % SIZE;               // Move tail forward with wrap-around
    count++;                                // Increase the count of elements
    printf("Enqueued: %d\n", value);
}

// Function to remove an element from the buffer
void dequeue() {
    if (is_empty()) {
        // Cannot remove element if buffer is empty
        printf("Buffer is empty. Cannot dequeue.\n");
        return;
    }
    int value = buffer[head];               // Get the element at the head
    head = (head + 1) % SIZE;               // Move head forward with wrap-around
    count--;                                // Decrease the count of elements
    printf("Dequeued: %d\n", value);
}

// Function to display the current contents of the buffer
void display() {
    if (is_empty()) {
        printf("Buffer is empty.\n");
        return;
    }
    printf("Buffer contents: ");
    for (int i = 0; i < count; i++) {
        // Use modulo to correctly handle wrap-around indexing
        printf("%d ", buffer[(head + i) % SIZE]);
    }
    printf("\n");
}

// Main function to test circular buffer operations
int main() {
    // Enqueue 5 elements into the buffer
    enqueue(5);
    enqueue(8);
    enqueue(6);
    enqueue(2);
    enqueue(9);

    // Attempt to enqueue into a full buffer
    enqueue(10);  // This should show a "Buffer is full" message

    // Display buffer contents
    display();

    // Dequeue two elements
    dequeue();  // Dequeues 5
    dequeue();  // Dequeues 8

    // Display buffer after dequeue
    display();

    // Enqueue two more elements (wrap-around happens here)
    enqueue(1);
    enqueue(8);

    // Final buffer display
    display();

    return 0;
}


