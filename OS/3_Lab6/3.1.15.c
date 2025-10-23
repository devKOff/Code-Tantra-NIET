#include <stdio.h>

/**
 * @brief Finds the index of the least recently used page.
 * This is the frame with the "oldest" timestamp (smallest time value).
 * * @param time An array where time[i] is the timestamp of the last use 
 * of the page in frame i.
 * @param n The number of frames.
 * @return The index (0 to n-1) of the frame holding the LRU page.
 */
int findLRU(int time[], int n) {
    int min = time[0];
    int pos = 0;

    // Iterate to find the smallest time value
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int num_frames, num_pages, page_faults = 0;
    
    // 1. Get the length of the page reference string
    printf("Enter number of pages: ");
    scanf("%d", &num_pages);
    
    int ref_string[num_pages];
    
    // 2. Get the page reference string
    printf("Enter the page reference string: ");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &ref_string[i]);
    }
    
    // 3. Get the number of available frames
    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    // frames[]: Stores the pages currently in memory
    int frames[num_frames];
    
    // time[]: Stores the "timestamp" (the loop index i) of when
    // each page in a frame was last used.
    int time[num_frames];
    
    // Initialize all frames to -1 (empty)
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        time[i] = -1; // Not used yet
    }

    // 4. Process the page reference string
    for (int i = 0; i < num_pages; i++) {
        int current_page = ref_string[i];
        int found = 0;
        
        // --- Page Hit ---
        // Check if the page is already in a frame
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == current_page) {
                found = 1;
                time[j] = i; // Update its "last used" time to now
                break;
            }
        }
        
        // --- Page Fault ---
        // If the page was not found
        if (found == 0) {
            page_faults++;
            
            // Check if there is an empty frame
            int empty_frame = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    empty_frame = j;
                    break;
                }
            }
            
            if (empty_frame != -1) {
                // If an empty frame exists, use it
                frames[empty_frame] = current_page;
                time[empty_frame] = i; // Set its "last used" time
            } else {
                // If no empty frames, find and replace the LRU page
                int lru_index = findLRU(time, num_frames);
                frames[lru_index] = current_page;
                time[lru_index] = i; // Set its "last used" time
            }
        }
    }
    
    // 5. Print the final result
    printf("Total Page Faults = %d\n", page_faults);
    
    return 0;
}