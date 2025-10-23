#include <stdio.h>

int main() {
    int n, m; // n = processes, m = resources

    printf("Enter processes and resources: ");
    scanf("%d %d", &n, &m);

    // Declare all the matrices and vectors needed
    int allocation[n][m];
    int max[n][m];
    int available[m];
    int need[n][m]; // This will be calculated
    
    int finish[n];      // Boolean flag for each process (0 = false, 1 = true)
    int safe_sequence[n]; // To store the resulting safe sequence
    int work[m];        // A temporary copy of the available vector

    // --- 1. Get User Input ---

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Max matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available vector:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    // --- 2. Initialize Data Structures ---

    // CRITICAL: Calculate the Need matrix (Need = Max - Allocation)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Make sure it is MAX - ALLOCATION
            need[i][j] = max[i][j] - allocation[i][j]; 
        }
    }

    // Initialize all processes as unfinished (finish[i] = 0)
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    // Initialize the 'work' vector to be equal to 'available'
    for (int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    // --- 3. Run the Safety Algorithm ---

    int count = 0; // Counter for safe sequence
    int found_process_this_pass; // Flag to check if we made progress

    do {
        found_process_this_pass = 0; // Reset flag for this new pass

        for (int i = 0; i < n; i++) {
            
            // Step 1: Find a process 'i' that is not finished
            if (finish[i] == 0) {
                
                // Step 2: Check if its 'Need' is <= 'Work'
                int can_run = 1; // Assume it can run
                for (int j = 0; j < m; j++) {
                    // CRITICAL: Check if NEED > WORK
                    if (need[i][j] > work[j]) { 
                        can_run = 0; // Cannot run
                        break;
                    }
                }

                // Step 3: If it can run (Need <= Work)
                if (can_run == 1) {
                    // "Run" the process: release its resources
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    
                    finish[i] = 1; // Mark as finished
                    safe_sequence[count++] = i; // Add to safe sequence
                    found_process_this_pass = 1; // We made progress
                }
            }
        }
    } while (found_process_this_pass == 1); // Loop again if we made progress

    // --- 4. Check the Result ---
    
    if (count == n) { // If all processes finished
        printf("No deadlock\n");
        printf("Safe sequence: ");
        for (int i = 0; i < n; i++) {
            // CRITICAL: Print from safe_sequence[i], NOT just 'i'
            printf("P%d ", safe_sequence[i]); 
        }
        printf("\n");
    } else {
        // Otherwise, a deadlock exists
        printf("Deadlock: ");
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) { // Print all unfinished (deadlocked) processes
                printf("P%d ", i);
            }
        }
        printf("\n");
    }

    return 0;
}