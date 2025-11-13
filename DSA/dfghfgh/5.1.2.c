#include <stdio.h>
#include <stdlib.h>

// Structure to represent an activity
struct Activity {
    int start;
    int end;
};

// Comparison function for sorting by end time
int compare(const void* a, const void* b) {
    struct Activity* act1 = (struct Activity*)a;
    struct Activity* act2 = (struct Activity*)b;
    return act1->end - act2->end; // Sort by end time (ascending)
}

int maxActivities(int n, struct Activity arr[]) {
    // Sort activities by end time
    qsort(arr, n, sizeof(struct Activity), compare);

    int count = 1; // First activity is always selected
    int lastEnd = arr[0].end; // End time of the last selected activity

    // Greedily select non-overlapping activities
    for (int i = 1; i < n; i++) {
        if (arr[i].start > lastEnd) {
            count++;
            lastEnd = arr[i].end;
        }
    }

    return count;
}

int main() {
    int n;
    scanf("%d", &n);

    struct Activity arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i].start);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i].end);
    }

    int result = maxActivities(n, arr);
    printf("%d\n", result);

    return 0;
}