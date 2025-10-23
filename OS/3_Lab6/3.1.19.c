#include <stdio.h>
#include <stdlib.h>

// Function to sort the request array
void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// LOOK Disk Scheduling Algorithm
void look(int requests[], int n, int head, int direction) {
    int seek_sequence[100], seek_count = 0, total_seek_time = 0;
    int i, j, pos;

    // Copy requests to a new array for sorting
    int sorted_requests[100];
    for (i = 0; i < n; i++) {
        sorted_requests[i] = requests[i];
    }
    sort(sorted_requests, n);

    // Find the position of the head in sorted array
    for (pos = 0; pos < n; pos++) {
        if (sorted_requests[pos] >= head)
            break;
    }

    // If direction is right (1)
    if (direction == 1) {
        // Move right: service requests >= head
        for (i = pos; i < n; i++) {
            seek_sequence[seek_count++] = sorted_requests[i];
            if (seek_count == 1)
                total_seek_time += abs(head - sorted_requests[i]);
            else
                total_seek_time += abs(seek_sequence[seek_count - 2] - sorted_requests[i]);
        }
        // Move left: service remaining requests
        for (i = pos - 1; i >= 0; i--) {
            seek_sequence[seek_count++] = sorted_requests[i];
            total_seek_time += abs(seek_sequence[seek_count - 2] - sorted_requests[i]);
        }
    }
    // If direction is left (0)
    else {
        // Move left: service requests <= head
        for (i = pos - 1; i >= 0; i--) {
            seek_sequence[seek_count++] = sorted_requests[i];
            if (seek_count == 1)
                total_seek_time += abs(head - sorted_requests[i]);
            else
                total_seek_time += abs(seek_sequence[seek_count - 2] - sorted_requests[i]);
        }
        // Move right: service remaining requests
        for (i = pos; i < n; i++) {
            seek_sequence[seek_count++] = sorted_requests[i];
            total_seek_time += abs(seek_sequence[seek_count - 2] - sorted_requests[i]);
        }
    }

    // Print seek sequence
    printf("Seek sequence:\n");
    printf("%d", head);
    for (i = 0; i < seek_count; i++) {
        printf(" -> %d", seek_sequence[i]);
    }
    printf(" -> End\n");

    // Print total seek time
    printf("Total seek time: %d\n", total_seek_time);
}

int main() {
    int n, head, direction;

    // Input number of disk requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    // Input disk requests
    int requests[100];
    printf("Enter the disk requests (in track numbers):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    // Input head position
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    // Input direction
    printf("Enter the direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    // Call LOOK algorithm
    look(requests, n, head, direction);

    return 0;
}