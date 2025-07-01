#include <stdio.h>
#include <stdbool.h>

#define SIZE 5  

int buffer[SIZE];
int head = 0;     
int tail = 0;     
int count = 0;    

bool is_full() {
    return count == SIZE;
}

bool is_empty() {
    return count == 0;
}

void enqueue(int value) {
    if (is_full()) {
        printf("Buffer is full. Cannot enqueue %d\n", value);
        return;
    }
    buffer[tail] = value;
    tail = (tail + 1) % SIZE;
    count++;
    printf("Enqueued: %d\n", value);
}

void dequeue() {
    if (is_empty()) {
        printf("Buffer is empty. Cannot dequeue.\n");
        return;
    }
    int value = buffer[head];
    head = (head + 1) % SIZE;
    count--;
    printf("Dequeued: %d\n", value);
}

void display() {
    if (is_empty()) {
        printf("Buffer is empty.\n");
        return;
    }
    printf("Buffer contents: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", buffer[(head + i) % SIZE]);
    }
    printf("\n");
}
int main() {
    enqueue(5);
    enqueue(8);
    enqueue(6);
    enqueue(2);
    enqueue(9);
    enqueue(10); 

    display();

    dequeue(9);
    dequeue();

    display();

    enqueue(1);
    enqueue(8);

    display();

    return 0;
}

