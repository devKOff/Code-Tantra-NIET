#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to parse a comma-separated string into an array of integers
int parseArray(const char *str, int arr[], int max_len) {
    char temp_str[10000];
    strncpy(temp_str, str, sizeof(temp_str) - 1);
    temp_str[sizeof(temp_str) - 1] = '\0';
    
    char *token = strtok(temp_str, ",");
    int count = 0;

    while (token != NULL && count < max_len) {
        // Skip any leading or trailing whitespace that might be present
        // (though not strictly necessary for the sample, it's safer)
        if (sscanf(token, "%d", &arr[count]) == 1) {
            count++;
        }
        token = strtok(NULL, ",");
    }
    return count;
}

// Function to merge two sorted arrays
void mergeSortedArrays(int arr1[], int n1, int arr2[], int n2, int result[]) {
    int i = 0; // Pointer for arr1
    int j = 0; // Pointer for arr2
    int k = 0; // Pointer for result

    // Merge loop: Compare elements of both arrays
    while (i < n1 && j < n2) {
        if (arr1[i] <= arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }

    // Copy remaining elements of arr1 (if any)
    while (i < n1) {
        result[k++] = arr1[i++];
    }

    // Copy remaining elements of arr2 (if any)
    while (j < n2) {
        result[k++] = arr2[j++];
    }
}

int main(int argc, char *argv[]) {
    // Check if exactly two argument strings are provided (besides the program name)
    if (argc != 3) {
        return 1;
    }

    // Maximum possible size for the temporary arrays and the final array
    // Assuming a reasonable max array size based on typical constraints.
    // We use a large, fixed size for simplicity since dynamic allocation isn't strictly necessary.
    const int MAX_TOTAL_SIZE = 1000; 

    int arr1[MAX_TOTAL_SIZE];
    int arr2[MAX_TOTAL_SIZE];
    int result[MAX_TOTAL_SIZE * 2];
    
    // Parse the two comma-separated string arguments
    int n1 = parseArray(argv[1], arr1, MAX_TOTAL_SIZE);
    int n2 = parseArray(argv[2], arr2, MAX_TOTAL_SIZE);
    int total_size = n1 + n2;
    
    // Perform the merge operation
    mergeSortedArrays(arr1, n1, arr2, n2, result);
    
    // Print the final merged array
    for (int k = 0; k < total_size; k++) {
        printf("%d", result[k]);
        if (k < total_size - 1) {
            printf(",");
        }
    }
    printf("\n");

    return 0;
}