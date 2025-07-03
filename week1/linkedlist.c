#include<stdio.h>
#include<stdlib.h>

// Define a node structure for the singly linked list

struct node {
    int data;              // Stores the value
    struct node *link;     // Pointer to the next node
};

// Function to count the number of nodes in the list

void count_of_nodes(struct node *head) {
    int count = 0;

    if (head == NULL) {
        printf("The list is empty\n");
        return;
    }

    // Pointer to traverse the list
	
    struct node *ptr = NULL;
    ptr = head;

    // Traverse until end of the list and count nodes
    while (ptr != NULL) {
        count++;
        ptr = ptr->link;
    }

    printf("The number of nodes is: %d\n", count);
}

// Function to print all node data
void print_data(struct node *head) {
    if (head == NULL) {
        printf("The list is empty\n");
        return;
    }

    struct node *ptr = NULL;
    ptr = head;

    // Print data in each node
    while (ptr != NULL) {
        printf("%d\n", ptr->data);
        ptr = ptr->link;
    }
}

// Function to add a node at the end of the list
void add_at_the_end(struct node *head, int data) {
    struct node *ptr, *temp;
    ptr = head;

    // Allocate memory for the new node
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;      // Set its data
    temp->link = NULL;      // It's the last node, so link is NULL

    // Traverse to the last node
    while (ptr->link != NULL) {
        ptr = ptr->link;
    }

    // Link the last node to the new node
    ptr->link = temp;
}

int main() {
    // Create the first node (head)
    struct node *head = malloc(sizeof(struct node));
    head->data = 43;
    head->link = NULL;

    // Create second node and link it to head
	
    struct node *current = malloc(sizeof(struct node));
    current->data = 32;
    current->link = NULL;
    head->link = current;

    // Create third node and link it to second node
	
    current = malloc(sizeof(struct node));
    current->data = 22;
    current->link = NULL;
    head->link->link = current;

    // Count and print the number of nodes
	
    count_of_nodes(head);

    // Print all node data
    print_data(head);

    // Add a new node with data 55 at the end
	
    add_at_the_end(head, 55);

    // Print the first three nodes again for confirmation
	
    printf("The added nodes are:\n%d\n%d\n%d\n", head->data, head->link->data, head->link->link->data);

    return 0;
}
