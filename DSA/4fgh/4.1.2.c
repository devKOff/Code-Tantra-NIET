#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000 // Maximum size of the circular queue

// Circular Queue structure
struct CircularQueue {
    int arr[MAX_SIZE];
    int front;
    int rear;
    int size; // Current number of elements
};

// Initialize circular queue
void initQueue(struct CircularQueue* q) {
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

// Check if queue is empty
int isEmpty(struct CircularQueue* q) {
    return q->size == 0;
}

// Check if queue is full
int isFull(struct CircularQueue* q) {
    return q->size == MAX_SIZE;
}

// Enqueue operation
void enqueue(struct CircularQueue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full\n"); // Optional message, can be removed
        return;
    }
    q->arr[q->rear] = value;
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->size++;
}

// Dequeue operation
void dequeue(struct CircularQueue* q) {
    if (isEmpty(q)) {
        return; // Ignore dequeue on empty queue
    }
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
}

// Print circular queue elements
void printQueue(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Empty\n");
        return;
    }
    int count = 0;
    int index = q->front;
    while (count < q->size) {
        printf("%d", q->arr[index]);
        if (count < q->size - 1) printf(" ");
        index = (index + 1) % MAX_SIZE;
        count++;
    }
    printf("\n");
}

int main() {
    struct CircularQueue q;
    initQueue(&q);

    int qOperations;
    scanf("%d", &qOperations);

    // Process each operation
    for (int i = 0; i < qOperations; i++) {
        int op;
        scanf("%d", &op);

        if (op == 1) { // Enqueue
            int value;
            scanf("%d", &value);
            enqueue(&q, value);
        } else if (op == 2) { // Dequeue
            dequeue(&q);
        }
    }

    // Print the final state of the queue
    printQueue(&q);

    return 0;
}