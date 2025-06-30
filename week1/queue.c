#include <stdio.h>
#define SIZE 5

int queue[SIZE];
int front = -1, rear = -1;

void enqueue(int value) {
    if (rear == SIZE - 1)
        printf("Queue is full\n");
    else {
        if (front == -1) front = 0;
        rear++;
        queue[rear] = value;
        printf("%d enqueued\n", value);
    }
}

void dequeue() {
    if (front == -1 || front > rear)
        printf("Queue is empty\n");
    else {
        printf("%d dequeued\n", queue[front]);
        front++;
    }
}

void display() {
    if (front == -1 || front > rear)
        printf("Queue is empty\n");
    else {
        printf("Queue: ");
        for (int i = front; i <= rear; i++)
            printf("%d ", queue[i]);
        printf("\n");
    }
}

int main() {
    enqueue(2);
    enqueue(3);
    enqueue(5);
    display();
    dequeue(5);
    display();
    return 0;
}
