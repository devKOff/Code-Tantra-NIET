#include <stdio.h>
#include <stdbool.h>

/**
 * Helper function to search for a page in the frames.
 * Returns true if the page is found (a "hit"), false otherwise.
 */
bool search(int key, int frames[], int capacity) {
    for (int i = 0; i < capacity; i++) {
        if (frames[i] == key) {
            return true;
        }
    }
    return false;
}

/**
 * Helper function to find the optimal page to replace.
 * It looks into the "future" (the rest of the page string) to decide
 * which page in the current frames will be used furthest in the future.
 */
int findOptimalVictim(int pages[], int frames[], int n, int capacity, int currentIndex) {
    int victim_frame_index = -1;
    int farthest_future_use = -1;

    // Iterate through each page currently in the frames
    for (int i = 0; i < capacity; i++) {
        int current_frame_page = frames[i];
        int j;

        // Search for the *next* use of this page in the *future* reference string
        for (j = currentIndex + 1; j < n; j++) {
            if (pages[j] == current_frame_page) {
                // If this page's next use is further than the current "farthest"
                if (j > farthest_future_use) {
                    farthest_future_use = j;
                    victim_frame_index = i;
                }
                break; // Found next use, stop searching for this frame's page
            }
        }

        // If the page is *never* used again in the future
        if (j == n) {
            return i; // This is the perfect victim, return its frame index immediately
        }
    }

    // If all pages in frames are used again, return the one used furthest in the future.
    // If victim_frame_index is still -1 (e.g., if all future uses are the same), 
    // we can default to replacing the first frame (or any frame).
    // But based on the logic, 'victim_frame_index' will be set correctly.
    if (victim_frame_index == -1) {
        return 0; // Default case, replace the first frame
    }
    
    return victim_frame_index;
}

/**
 * Main function to simulate the Optimal Page Replacement Algorithm
 */
int main() {
    int n;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    int capacity;
    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    // Initialize all frames to -1 (to represent empty)
    int frames[capacity];
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    int page_faults = 0;
    int empty_frame_pointer = 0; // Tracks the next available empty frame

    // Iterate through each page in the reference string
    for (int i = 0; i < n; i++) {
        int current_page = pages[i];

        // 1. Check for a HIT
        // If the page is already in a frame, it's a hit.
        if (search(current_page, frames, capacity)) {
            continue; // Go to the next page
        }

        // It's a FAULT
        page_faults++;

        // 2. Check for an EMPTY frame
        // If there is still space in the frames
        if (empty_frame_pointer < capacity) {
            frames[empty_frame_pointer] = current_page;
            empty_frame_pointer++; // Move to the next empty frame
        } 
        // 3. Find the OPTIMAL victim to replace
        // If all frames are full
        else {
            int victim_index = findOptimalVictim(pages, frames, n, capacity, i);
            frames[victim_index] = current_page;
        }
    }

    printf("Total Page Faults = %d\n", page_faults);

    return 0;
}