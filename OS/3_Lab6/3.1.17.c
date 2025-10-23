#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max disk size
#define DISK_END 199
#define DISK_START 0
#define MAX_REQUESTS 20

// Helper function for qsort() to sort integers
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int num_requests;
    int requests[MAX_REQUESTS];
    int head_pos;
    char direction[10];
    int total_seek = 0;
    int current_pos;

    // --- Arrays to store the final output ---
    // We need space for all requests + 1 (for the disk end, e.g., 0 or 199)
    int seek_sequence[MAX_REQUESTS + 1];
    int seq_count = 0;

    // 1. Get number of requests
    printf("Enter number of disk requests (max %d): ", MAX_REQUESTS);
    scanf("%d", &num_requests);

    // 2. Get the requests
    printf("Enter the disk requests (space separated): ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }

    // 3. Get initial head position
    printf("Enter initial head position (0-%d): ", DISK_END);
    scanf("%d", &head_pos);

    // 4. Get direction
    printf("Enter direction (left/right): ");
    scanf("%s", direction);

    // 5. Sort the requests to make the SCAN algorithm simple
    qsort(requests, num_requests, sizeof(int), compare);

    // Find the "split point" - the first request >= head position
    int split_point = 0;
    while (split_point < num_requests && requests[split_point] < head_pos) {
        split_point++;
    }

    current_pos = head_pos;

    if (strcmp(direction, "left") == 0) {
        // --- Go Left ---
        for (int i = split_point - 1; i >= 0; i--) {
            total_seek += (current_pos - requests[i]);
            current_pos = requests[i];
            seek_sequence[seq_count++] = current_pos; // Store in sequence
        }
        
        // Hit the end (DISK_START)
        total_seek += (current_pos - DISK_START);
        current_pos = DISK_START;
        seek_sequence[seq_count++] = current_pos; // Store in sequence

        // --- Go Right ---
        for (int i = split_point; i < num_requests; i++) {
            total_seek += (requests[i] - current_pos);
            current_pos = requests[i];
            seek_sequence[seq_count++] = current_pos; // Store in sequence
        }

    } else { // Direction is "right"
        // --- Go Right ---
        for (int i = split_point; i < num_requests; i++) {
            total_seek += (requests[i] - current_pos);
            current_pos = requests[i];
            seek_sequence[seq_count++] = current_pos; // Store in sequence
        }

        // Hit the end (DISK_END)
        total_seek += (DISK_END - current_pos);
        current_pos = DISK_END;
        seek_sequence[seq_count++] = current_pos; // Store in sequence

        // --- Go Left ---
        for (int i = split_point - 1; i >= 0; i--) {
            total_seek += (current_pos - requests[i]);
            current_pos = requests[i];
            seek_sequence[seq_count++] = current_pos; // Store in sequence
        }
    }

    // --- Print the final results in the correct order ---
    
    // 1. Print Total Seek Operations
    printf("Total Seek Operations: %d\n", total_seek);

    // 2. Print the stored Seek Sequence
    printf("Seek Sequence: ");
    for (int i = 0; i < seq_count; i++) {
        printf("%d ", seek_sequence[i]);
    }
    printf("\n"); // Add the final newline

    return 0;
}