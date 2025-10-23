#include <stdio.h>

int main() {
    int increments_p1, increments_p2;
    int counter = 0;

    // Input for Process 1 increments
    printf("Enter how many times Process 1 should increment the counter: ");
    scanf("%d", &increments_p1);

    // Input for Process 2 increments
    printf("Enter how many times Process 2 should increment the counter: ");
    scanf("%d", &increments_p2);

    // Simulate Process 1 increments
    for (int i = 0; i < increments_p1; i++) {
        counter++;
    }

    // Simulate Process 2 increments
    for (int i = 0; i < increments_p2; i++) {
        counter++;
    }

    // Output the final counter value
    printf("Final counter value (expected: %d): %d\n", increments_p1 + increments_p2, counter);

    return 0;
}