#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insertNode(struct Node** headRef, int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return;
    }
    newNode->data = val;

    if (*headRef == NULL) {
        *headRef = newNode;
        newNode->next = *headRef;
        return;
    }

    struct Node* current = *headRef;
    while (current->next != *headRef) {
        current = current->next;
    }

    current->next = newNode;
    newNode->next = *headRef;
}

void deleteNode(struct Node** headRef, int val) {
    if (*headRef == NULL) {
        return;
    }

    struct Node* current = *headRef;
    struct Node* prev = NULL;

    do {
        if (current->data == val) {
            break;
        }
        prev = current;
        current = current->next;
    } while (current != *headRef);

    if (current->data != val) {
        return; 
    }

    if (current == *headRef && current->next == *headRef) {
        *headRef = NULL;
        free(current);
        return;
    }

    if (current == *headRef) {
        struct Node* tail = *headRef;
        while (tail->next != *headRef) {
            tail = tail->next;
        }
        
        *headRef = current->next;
        tail->next = *headRef;
    } 
    else {
        prev->next = current->next;
    }

    free(current);
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
        if (scanf("%d %d", &op, &val) != 2) break;
        
        if (op == 1) {
            insertNode(&head, val);
        } else if (op == 2) {
            deleteNode(&head, val);
        }
    }

    displayList(head);

    if (head != NULL) {
        struct Node* current = head->next;
        struct Node* nextNode;
        while (current != head) {
            nextNode = current->next;
            free(current);
            current = nextNode;
        }
        free(head);
    }

    return 0;
}