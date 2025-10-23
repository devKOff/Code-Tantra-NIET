#include <stdio.h>
#include <stdlib.h>

// Helper function for qsort() to sort integers
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

#define MAX_REQUESTS 20

int main() {
    int num_requests;
    int requests[MAX_REQUESTS];
    int head_pos;
    int disk_size;
    int total_seek = 0;
    int current_pos;

    // 1. Get number of requests
    printf("Enter number of disk requests: ");
    scanf("%d", &num_requests);

    // 2. Get the requests
    printf("Enter the disk requests (space separated): ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }

    // 3. Get initial head position
    printf("Enter initial head position: ");
    scanf("%d", &head_pos);
    
    // 4. Get disk size
    printf("Enter disk size (max cylinder number): ");
    scanf("%d", &disk_size);

    // 5. Sort the requests
    qsort(requests, num_requests, sizeof(int), compare);

    // 6. Find the split point (first request >= head)
    int split_point = 0;
    while (split_point < num_requests && requests[split_point] < head_pos) {
        split_point++;
    }

    // --- 7. Calculate Seek and Print Sequence ---
    
    // Start printing the sequence
    printf("Seek Sequence: %d", head_pos);
    current_pos = head_pos;

    // --- Go Right (from head to end) ---
    for (int i = split_point; i < num_requests; i++) {
        total_seek += (requests[i] - current_pos);
        current_pos = requests[i];
        printf(" -> %d", current_pos);
    }

    // --- Go to End of Disk ---
    total_seek += (disk_size - current_pos);
    current_pos = disk_size;
    printf(" -> %d (Jump to end)", current_pos);

    // --- Jump to Start of Disk ---
    // This logic includes the full jump in the seek time
    total_seek += (disk_size - 0);
    current_pos = 0;
    printf(" -> %d (Jump to start)", current_pos);

    // --- Go Right (from start to last request) ---
    for (int i = 0; i < split_point; i++) {
        total_seek += (requests[i] - current_pos);
        current_pos = requests[i];
        printf(" -> %d", current_pos);
    }

    // --- 8. Print Total Seek Operations ---
    
    // THE FIX: Add a newline to end the "Seek Sequence" line
    printf("\n"); 
    
    // Print "Total Seek Operations" on its own, new line
    printf("Total Seek Operations: %d\n", total_seek);

    return 0;
}