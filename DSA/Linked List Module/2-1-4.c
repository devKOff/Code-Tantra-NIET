#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

void insertNode(struct Node** headRef, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return;
    }
    newNode->data = val;

    if (*headRef == NULL) {
        *headRef = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
        return;
    }

    struct Node* tail = (*headRef)->prev;
    
    newNode->next = *headRef;
    newNode->prev = tail;
    (*headRef)->prev = newNode;
    tail->next = newNode;
}

void deleteLastNode(struct Node** headRef) {
    if (*headRef == NULL) {
        return;
    }

    if ((*headRef)->next == *headRef) {
        free(*headRef);
        *headRef = NULL;
        return;
    }

    struct Node* tail = (*headRef)->prev;
    struct Node* newTail = tail->prev;

    newTail->next = *headRef;
    (*headRef)->prev = newTail;

    free(tail);
}

void displayList(struct Node* head) {
    if (head == NULL) {
        printf("\n");
        return;
    }

    struct Node* temp = head;
    do {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp != head) {
            printf(" ");
        }
    } while (temp != head);
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int n, op, val;

    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &op) != 1) {
            break;
        }

        if (op == 1) {
            if (scanf("%d", &val) != 1) {
                break;
            }
            insertNode(&head, val);
        } else if (op == 2) {
            deleteLastNode(&head);
        }
    }

    displayList(head);

    if (head != NULL) {
        struct Node* current = head->next;
        struct Node* nextNode;
        head->prev->next = NULL;
        while (current != NULL) {
            nextNode = current->next;
            free(current);
            current = nextNode;
            if (current == head) break; 
        }
        free(head);
    }

    return 0;
}