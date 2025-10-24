#include <stdio.h>
#include <stdlib.h>

// Structure for a node in a double-linked list
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Function to insert a new node at the end of the list
void insertNode(struct Node** headRef, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return;
    }
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

// Function to delete the first occurrence of a node with the given value
void deleteNode(struct Node** headRef, int val) {
    struct Node* current = *headRef;

    while (current != NULL) {
        if (current->data == val) {
            // Case 1: Node is the head
            if (current->prev == NULL) {
                *headRef = current->next;
                if (*headRef != NULL) {
                    (*headRef)->prev = NULL;
                }
            }
            // Case 2: Node is the tail (or a middle node)
            else {
                current->prev->next = current->next;
                if (current->next != NULL) {
                    current->next->prev = current->prev;
                }
            }
            free(current);
            return; 
        }
        current = current->next;
    }
    // Note: If the element is not found, the function simply returns,
    // which aligns with the problem's note.
}

// Function for traversal and display (Output)
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
    struct Node* head = NULL;
    int n, op, val;

    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        if (scanf("%d %d", &op, &val) != 2) break;
        
        if (op == 1) {
            insertNode(&head, val);
        } else if (op == 2) {
            deleteNode(&head, val);
        }
    }

    // Traversal and display the final list
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