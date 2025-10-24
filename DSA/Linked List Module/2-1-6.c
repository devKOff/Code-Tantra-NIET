#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createList() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int val;

    while (scanf("%d", &val) == 1 && val != -1) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) return NULL; 
        newNode->data = val;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
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

void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int isPalindrome(struct Node* head) {
    if (head == NULL || head->next == NULL) {
        return 1;
    }

    struct Node *slow = head, *fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    struct Node* second_half = reverseList(slow);
    
    struct Node* list1 = head;
    struct Node* list2 = second_half;
    int is_palindrome = 1;
    
    while (list2 != NULL) {
        if (list1->data != list2->data) {
            is_palindrome = 0;
            break;
        }
        list1 = list1->next;
        list2 = list2->next;
    }

    return is_palindrome;
}

int main() {
    int t;
    if (scanf("%d", &t) != 1 || t > 102) return 0;

    char results[102][6]; 

    for (int i = 0; i < t; i++) {
        struct Node* head = createList();
        
        if (isPalindrome(head)) {
            strcpy(results[i], "true");
        } else {
            strcpy(results[i], "false");
        }

        freeList(head);
    }

    // Print all results at once after the loop
    for (int i = 0; i < t; i++) {
        printf("%s\n", results[i]);
    }

    return 0;
}