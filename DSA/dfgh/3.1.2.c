#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
struct Node {
    int data;
    struct Node* next;
};

// Stack structure
struct Stack {
    struct Node* top;
};

// Initialize stack
void initStack(struct Stack* stack) {
    stack->top = NULL;
}

// Check if stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Push operation
void push(struct Stack* stack, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Pop operation
void pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        struct Node* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
}

// Peek operation
int peek(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->top->data;
    }
    return -1; // Return -1 for empty stack (won't be printed)
}

// Print stack elements
void printStack(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Empty\n");
        return;
    }
    struct Node* current = stack->top;
    while (current) {
        printf("%d", current->data);
        if (current->next) printf("->");
        current = current->next;
    }
    printf("\n");
}

// Free stack
void freeStack(struct Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
}

int main() {
    struct Stack stack;
    initStack(&stack);
    
    int N;
    scanf("%d", &N);
    
    // Process each operation
    for (int i = 0; i < N; i++) {
        int op;
        scanf("%d", &op);
        
        if (op == 1) { // Push
            int value;
            scanf("%d", &value);
            push(&stack, value);
        } else if (op == 2) { // Pop
            pop(&stack);
        } else if (op == 3) { // Peek
            if (!isEmpty(&stack)) {
                printf("%d", peek(&stack));
            }
        }
    }
    
    // Print final stack
    printStack(&stack);
    
    // Free stack memory
    freeStack(&stack);
    
    return 0;
}