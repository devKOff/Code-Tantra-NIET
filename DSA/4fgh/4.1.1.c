#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000 // Maximum size of the queue

// Queue structure
struct Queue {
    int arr[MAX_SIZE];
    int front;
    int rear;
};

// Initialize queue
void initQueue(struct Queue* q) {
    q->front = 0;
    q->rear = 0;
}

// Check if queue is empty
int isEmpty(struct Queue* q) {
    return q->front == q->rear;
}

// Enqueue operation
void enqueue(struct Queue* q, int value) {
    if (q->rear < MAX_SIZE) {
        q->arr[q->rear++] = value;
    }
    // Note: No overflow handling as per problem constraints; assume sufficient size
}

// Dequeue operation
void dequeue(struct Queue* q) {
    if (!isEmpty(q)) {
        q->front++;
    }
    // Note: No underflow handling beyond empty check as per problem
}

// Print queue elements
void printQueue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Empty\n");
    } else {
        for (int i = q->front; i < q->rear; i++) {
            printf("%d", q->arr[i]);
            if (i < q->rear - 1) printf(" ");
        }
        printf("\n");
    }
}

int main() {
    struct Queue q;
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