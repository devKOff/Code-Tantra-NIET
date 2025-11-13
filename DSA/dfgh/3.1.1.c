#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

// Stack structure
struct Stack {
    int arr[MAX_SIZE];
    int top;
};

// Initialize stack
void initStack(struct Stack* stack) {
    stack->top = -1;
}

// Check if stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Check if stack is full
int isFull(struct Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// Push operation
void push(struct Stack* stack, int value) {
    if (!isFull(stack)) {
        stack->arr[++stack->top] = value;
    }
}

// Pop operation
void pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        stack->top--;
    }
}

// Peek operation
int peek(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->arr[stack->top];
    }
    return -1; // Return -1 for empty stack (won't be printed)
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
    if (isEmpty(&stack)) {
        printf("Empty\n");
    } else {
        // Print from top to bottom (reverse order)
        for (int i = stack.top; i >= 0; i--) {
            printf("%d", stack.arr[i]);
            if (i > 0) printf(" ");
        }
        printf("\n");
    }
    
    return 0;
}