#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Node {
    int coeff;
    int exp;
    struct Node *next;
};

struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) return NULL;
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

void insertTerm(struct Node** headRef, int coeff, int exp) {
    if (coeff == 0) return;

    struct Node* current = *headRef;
    struct Node* prev = NULL;

    while (current != NULL && exp <= current->exp) {
        if (exp == current->exp) {
            current->coeff += coeff;
            if (current->coeff == 0) {
                if (prev == NULL) {
                    *headRef = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current);
            }
            return;
        }
        prev = current;
        current = current->next;
    }

    struct Node* newNode = createNode(coeff, exp);
    if (newNode == NULL) return;
    
    if (prev == NULL) {
        newNode->next = *headRef;
        *headRef = newNode;
        return;
    }
    
    newNode->next = current;
    prev->next = newNode;
}

struct Node* readPolynomial() {
    int numTerms, coeff, exp;
    struct Node* head = NULL;
    
    if (scanf("%d", &numTerms) != 1) return NULL;

    for (int i = 0; i < numTerms; i++) {
        if (scanf("%d %d", &coeff, &exp) != 2) break;
        insertTerm(&head, coeff, exp);
    }
    return head;
}

struct Node* copyPolynomial(struct Node* poly) {
    struct Node* newHead = NULL;
    while (poly != NULL) {
        insertTerm(&newHead, poly->coeff, poly->exp);
        poly = poly->next;
    }
    return newHead;
}

struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    // We must copy poly1's terms first
    struct Node* temp1 = poly1;
    while (temp1 != NULL) {
        insertTerm(&result, temp1->coeff, temp1->exp);
        temp1 = temp1->next;
    }

    // Then merge poly2's terms
    struct Node* temp2 = poly2;
    while (temp2 != NULL) {
        insertTerm(&result, temp2->coeff, temp2->exp);
        temp2 = temp2->next;
    }

    return result;
}

void displayPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("0x^0\n"); // Handle empty polynomial
        return;
    }

    struct Node* current = head;
    while (current != NULL) {
        printf("%dx^%d", current->coeff, current->exp);
        
        current = current->next;
        if (current != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
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

int main() {
    // Read Polynomial 1
    struct Node* poly1 = readPolynomial();
    
    // Read Polynomial 2
    struct Node* poly2 = readPolynomial();
    
    // 1. Display the First Polynomial
    displayPolynomial(poly1);

    // 2. Display the Second Polynomial
    displayPolynomial(poly2);
    
    // 3. Calculate and Display the Sum
    struct Node* result = addPolynomials(poly1, poly2);
    displayPolynomial(result);

    // Free memory
    freeList(poly1);
    freeList(poly2);
    freeList(result);

    return 0;
}