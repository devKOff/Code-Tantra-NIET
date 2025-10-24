#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int x;
    scanf("%d", &x);

    // Sort the array first, as required by the problem notes
    // Using a simple Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Binary Search to find the LAST occurrence
    int low = 0;
    int high = n - 1;
    int result = -1; // Store the result, default to -1 (not found)

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x) {
            result = mid;      // Found an occurrence, store its position
            low = mid + 1;     // Keep searching to the right for the last occurrence
        } else if (arr[mid] < x) {
            low = mid + 1;     // The element is in the right half
        } else {
            high = mid - 1;    // The element is in the left half
        }
    }

    printf("%d\n", result);

    return 0;
}