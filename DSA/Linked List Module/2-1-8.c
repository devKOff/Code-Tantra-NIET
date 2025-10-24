#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insertAtEnd(struct Node** headRef, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) return;
    
    newNode->data = val;
    newNode->next = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    struct Node* last = *headRef;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}

void findMidpoint(struct Node* head) {
    if (head == NULL) {
        return;
    }

    struct Node* slow = head;
    struct Node* fast = head;

    // The condition (fast != NULL && fast->next != NULL) finds the FIRST middle element
    // To find the SECOND middle element (for even length), the fast pointer should start one step ahead.
    // However, the standard approach that naturally yields the second middle node for even lengths is:
    // slow moves one step, fast moves two steps.

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // For odd length (5, 6, 9, 8, 7), slow stops at 9 (the middle).
    // For even length (1, 2, 3, 4, 5, 6), slow stops at 4 (the second middle element, index 3).
    
    printf("%d\n", slow->data);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    struct Node* head = NULL;
    int val;

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &val) != 1) return 0;
        insertAtEnd(&head, val);
    }

    findMidpoint(head);

    // Free memory
    struct Node* current = head;
    struct Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    return 0;
}