#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition for singly-linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to detect a loop using Floyd's Cycle-Finding Algorithm
bool hasLoop(struct Node* head) {
    if (!head || !head->next) return false;
    
    struct Node *slow = head, *fast = head;
    
    // Move slow by 1 and fast by 2
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        // If they meet, there is a loop
        if (slow == fast) return true;
    }
    
    // If fast reaches the end, no loop
    return false;
}

int main() {
    int N, X;
    
    // Read number of nodes
    scanf("%d", &N);
    
    // Read node values
    int values[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &values[i]);
    }
    
    // Read position where tail connects
    scanf("%d", &X);
    
    // Create linked list
    struct Node* head = NULL;
    struct Node* tail = NULL;
    struct Node* nodes[N]; // To store node pointers for connecting the loop
    
    // Initialize linked list
    for (int i = 0; i < N; i++) {
        struct Node* newNode = createNode(values[i]);
        nodes[i] = newNode; // Store node pointer
        
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    // Create loop if X >= 1
    if (X >= 1 && X <= N) {
        tail->next = nodes[X-1]; // Connect tail to node at position X (1-based)
    }
    
    // Check for loop and print result
    printf("%s\n", hasLoop(head) ? "True" : "False");
    
    // Free allocated memory (optional, as program terminates)
    struct Node* current = head;
    while (current && N--) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    
    return 0;
}