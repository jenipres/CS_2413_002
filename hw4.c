#include <stdio.h>

#define MAX_SIZE 100

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Max-heap insert using variables x (heap), y (size), z (value)
void insert(int x[], int *y, int z) {
    x[*y] = z;          // Insert z at the end
    int i = *y;
    (*y)++;

    // Bubble-up to maintain max-heap
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (x[parent] < x[i]) {
            swap(&x[parent], &x[i]);
            i = parent;
        } else {
            break;
        }
    }
}

// Print the heap (x) as array
void printHeap(int x[], int y) {
    printf("Heap: ");
    for (int i = 0; i < y; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");
}

int main() {
    int x[MAX_SIZE] = {52, 32, 42, 22, 12, 27, 37, 12, 7}; // Initial heap
    int y = 9;

    insert(x, &y, 35);
    printHeap(x, y);

    insert(x, &y, 24);
    printHeap(x, y);

    insert(x, &y, 10);
    printHeap(x, y);

    return 0;
}
