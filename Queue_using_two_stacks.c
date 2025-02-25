#include <stdio.h>
#include <stdlib.h>

// Node structure for stack
typedef struct Node {
    int x;           // Data field
    struct Node* y;  // Pointer to next node
} Node;

// Stack structure
typedef struct Stack {
    Node* z;  // Pointer to the top of the stack
} Stack;

// Queue structure using two stacks
typedef struct Queue {
    Stack* x;  // First stack
    Stack* y;  // Second stack
} Queue;

// Function to create a new node
Node* createNode(int x) {
    Node* y = (Node*)malloc(sizeof(Node));  // Allocate memory for new node
    if (!y) {  // Check if memory allocation failed
        printf("Memory allocation failed\n");
        exit(1);
    }
    y->x = x;  // Assign data
    y->y = NULL;  // Initialize next pointer to NULL
    return y;  // Return newly created node
}

// Function to initialize a stack
Stack* createStack() {
    Stack* x = (Stack*)malloc(sizeof(Stack));  // Allocate memory for stack
    x->z = NULL;  // Initialize top pointer to NULL
    return x;  // Return newly created stack
}

// Function to push an element onto the stack
void push(Stack* x, int y) {
    Node* z = createNode(y);  // Create new node with data
    z->y = x->z;  // Point new node's next to current top
    x->z = z;  // Update top to new node
}

// Function to check if a stack is empty
int isEmpty(Stack* x) {
    return x->z == NULL;  // Return true if top is NULL
}

// Function to pop an element from the stack
int pop(Stack* x) {
    if (isEmpty(x)) {  // Check if stack is empty
        printf("Queue underflow\n");
        exit(1);
    }
    Node* y = x->z;  // Store reference to top node
    int z = y->x;  // Retrieve data from top node
    x->z = x->z->y;  // Move top pointer to next node
    free(y);  // Free memory of popped node
    return z;  // Return popped value
}

// Function to initialize a queue
Queue* createQueue() {
    Queue* x = (Queue*)malloc(sizeof(Queue));  // Allocate memory for queue
    x->x = createStack();  // Create first stack
    x->y = createStack();  // Create second stack
    return x;  // Return newly created queue
}

// Enqueue operation
void enqueue(Queue* x, int y) {
    push(x->x, y);  // Push element onto stack1
}

// Dequeue operation
int dequeue(Queue* x) {
    if (isEmpty(x->x) && isEmpty(x->y)) {  // Check if both stacks are empty
        printf("Queue is empty\n");
        exit(1);
    }

    if (isEmpty(x->y)) {  // If stack2 is empty, move all elements from stack1 to stack2
        while (!isEmpty(x->x)) {
            push(x->y, pop(x->x));  // Pop from stack1 and push to stack2
        }
    }
    return pop(x->y);  // Pop from stack2 (dequeue operation)
}

// Function to display the queue
void display(Queue* x) {
    Stack* y = createStack();  // Temporary stack to store values
    
    while (!isEmpty(x->y)) {  // Move elements from stack2 to temp stack
        push(y, pop(x->y));
    }

    while (!isEmpty(x->x)) {  // Move elements from stack1 to temp stack
        push(y, pop(x->x));
    }

    printf("Queue elements: ");
    while (!isEmpty(y)) {  // Print values and restore them back
        int z = pop(y);
        printf("%d ", z);
        push(x->x, z);
    }
    
    while (!isEmpty(x->y)) {  // Restore elements back to stack2
        push(y, pop(x->y));
    }

    free(y);  // Free memory of temporary stack
    printf("\n");
}

// Main function
int main() {
    Queue* x = createQueue();  // Create queue

    enqueue(x, 10);  // Enqueue 10
    enqueue(x, 20);  // Enqueue 20
    enqueue(x, 30);  // Enqueue 30

    printf("Dequeued: %d\n", dequeue(x));  // Dequeue and print element
    
    enqueue(x, 40);  // Enqueue 40
    
    printf("Dequeued: %d\n", dequeue(x));  // Dequeue and print element
    
    display(x);  // Display queue elements

    return 0;  // End program
}
