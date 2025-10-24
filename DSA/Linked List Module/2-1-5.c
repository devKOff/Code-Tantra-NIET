#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insertAtEnd(struct Node** headRef, int val) {
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

struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
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
    if (scanf("%d", &n) != 1 || n < 1 || n > 1000) {
        return 0;
    }

    struct Node* head = NULL;
    int val;

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &val) != 1) {
            return 0;
        }
        insertAtEnd(&head, val);
    }

    head = reverseList(head);

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