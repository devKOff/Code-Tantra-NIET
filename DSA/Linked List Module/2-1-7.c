#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

void insertAtEnd(struct Node** headRef, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) return;
    
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    struct Node* last = *headRef;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
    newNode->prev = last;
}

void reverseList(struct Node** headRef) {
    struct Node* current = *headRef;
    struct Node* temp = NULL;
    
    // Check for empty or single-node list
    if (current == NULL || current->next == NULL) {
        return;
    }

    // Traverse the list and swap next and prev pointers for every node
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        
        // Move to the next node (which is now stored in current->prev)
        current = current->prev; 
    }

    // Update the head: 'temp' now holds the pointer to the old head's next (which is the new head's prev)
    // The new head is the last node visited, which is the node just before 'current' became NULL.
    // Since 'temp' points to the old head (the new tail), the new head is temp->prev (before final swap).
    // After the loop, the original tail is now pointed to by temp's prev, so the new head is temp->prev.
    if (temp != NULL) {
        *headRef = temp->prev;
    }
}

void displayList(struct Node* node) {
    while (node != NULL) {
        printf("%d", node->data);
        node = node->next;
        if (node != NULL) {
            printf(" ");
        }
    }
    printf("\n");
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

    reverseList(&head);

    displayList(head);

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