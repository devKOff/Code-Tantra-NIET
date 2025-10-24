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

void deleteNode(struct Node** headRef, int val) {
    struct Node* temp = *headRef;
    struct Node* prev = NULL;

    if (temp != NULL && temp->data == val) {
        *headRef = temp->next; 
        free(temp);            
        return;
    }

    while (temp != NULL && temp->data != val) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void displayList(struct Node* node) {
    while (node != NULL) {
        printf("%d", node->data);
        node = node->next;
        if (node != NULL) {
            printf(" ");
        }
    }
    printf(" \n");
}

int main() {
    struct Node* head = NULL;
    int n, op, val;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &op, &val);
        if (op == 1) {
            insertNode(&head, val);
        } else if (op == 2) {
            deleteNode(&head, val);
        }
    }

    displayList(head);

    struct Node* current = head;
    struct Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    return 0;
}