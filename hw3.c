#include <stdio.h>
#include <stdlib.h>

// Definition of a tree node with renamed variables: x for key, y for left, z for right.
typedef struct Node {
    int x;
    struct Node *y, *z;
} Node;

// Function to create a new node
Node* createNode(int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->x = x;
    newNode->y = newNode->z = NULL;
    return newNode;
}

// Function to insert a value into the BST
Node* insert(Node* root, int x) {
    if (root == NULL) {
        return createNode(x);
    }
    if (x < root->x) {
        root->y = insert(root->y, x);
    } else {
        root->z = insert(root->z, x);
    }
    return root;
}

// In-order traversal: Left, Root, Right
void inorder(Node* root) {
    if (root) {
        inorder(root->y);
        printf("%d ", root->x);
        inorder(root->z);
    }
}

// Pre-order traversal: Root, Left, Right
void preorder(Node* root) {
    if (root) {
        printf("%d ", root->x);
        preorder(root->y);
        preorder(root->z);
    }
}

// Post-order traversal: Left, Right, Root
void postorder(Node* root) {
    if (root) {
        postorder(root->y);
        postorder(root->z);
        printf("%d ", root->x);
    }
}

// Helper function to find the minimum node in a subtree
Node* findMin(Node* root) {
    while (root && root->y != NULL)
        root = root->y;
    return root;
}

// Function to delete a node with a given value from the BST
Node* deleteNode(Node* root, int x) {
    if (root == NULL)
        return root;
    
    if (x < root->x)
        root->y = deleteNode(root->y, x);
    else if (x > root->x)
        root->z = deleteNode(root->z, x);
    else {
        // Node to be deleted found
        if (root->y == NULL) {
            Node* temp = root->z;
            free(root);
            return temp;
        } else if (root->z == NULL) {
            Node* temp = root->y;
            free(root);
            return temp;
        }
        // Node with two children: Get the inorder successor (smallest in right subtree)
        Node* temp = findMin(root->z);
        root->x = temp->x;
        root->z = deleteNode(root->z, temp->x);
    }
    return root;
}

int main() {
    Node* root = NULL;
    int i;
    
    // Initial BST creation with given values (assumed tree)
    int initialValues[] = {50, 30, 70, 20, 40, 60, 80};
    int nInitial = sizeof(initialValues) / sizeof(initialValues[0]);
    for(i = 0; i < nInitial; i++){
        root = insert(root, initialValues[i]);
    }
    
    // Display traversals of the initial BST
    printf("Initial BST Traversals:\n");
    printf("In-order: ");
    inorder(root);
    printf("\nPre-order: ");
    preorder(root);
    printf("\nPost-order: ");
    postorder(root);
    printf("\n\n");
    
    // Delete the root node (value = 50)
    printf("Deleting the root node (50)...\n");
    root = deleteNode(root, 50);
    printf("In-order after deleting root: ");
    inorder(root);
    printf("\n\n");
    
    // Insert new values: 11, 22, 33, 44, 55, 66, 77
    int newValues[] = {11, 22, 33, 44, 55, 66, 77};
    int nNew = sizeof(newValues) / sizeof(newValues[0]);
    for(i = 0; i < nNew; i++){
        root = insert(root, newValues[i]);
    }
    
    // Final in-order traversal after insertion of new nodes
    printf("In-order after inserting new values (11, 22, 33, 44, 55, 66, 77): ");
    inorder(root);
    printf("\n");
    
    return 0;
}
