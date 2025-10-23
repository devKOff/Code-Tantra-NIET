#include <stdio.h>
#include <stdlib.h> // For malloc, calloc, and free

// Structure to store the details of a found treasure
typedef struct {
    int r;
    int c;
    int v;
} Treasure;

// Global variables
int N, M;
int** grid;
int** visited;
Treasure* treasures; // Array to store found treasures
int treasureCount;

/**
 * @brief Performs a Depth-First Search (DFS) to find treasures.
 * @param r The current row.
 * @param c The current column.
 */
void dfs(int r, int c) {
    // 1. Check for out-of-bounds or if already visited
    if (r < 0 || r >= N || c < 0 || c >= M || visited[r][c]) {
        return;
    }

    // 2. Mark the current cell as visited
    visited[r][c] = 1;

    // 3. Check if the current cell is a treasure (non-zero)
    if (grid[r][c] != 0) {
        // It's a treasure. Add it to our list and stop this path.
        treasures[treasureCount].r = r;
        treasures[treasureCount].c = c;
        treasures[treasureCount].v = grid[r][c];
        treasureCount++;
        return; // Stop exploring this path
    }

    // 4. If we are here, grid[r][c] is 0 (a path).
    // Recurse in all 4 directions.
    dfs(r + 1, c); // Down
    dfs(r - 1, c); // Up
    dfs(r, c + 1); // Right
    dfs(r, c - 1); // Left
}

int main() {
    // Read grid dimensions
    scanf("%d %d", &N, &M);

    // --- Allocate memory for 2D arrays and treasure list ---
    grid = (int**)malloc(N * sizeof(int*));
    visited = (int**)malloc(N * sizeof(int*));
    treasures = (Treasure*)malloc(N * M * sizeof(Treasure));

    for (int i = 0; i < N; i++) {
        grid[i] = (int*)malloc(M * sizeof(int));
        visited[i] = (int*)calloc(M, sizeof(int));
    }
    // --------------------------------------------------------

    // Read the grid values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    treasureCount = 0;

    // --- Problem Logic ---

    // Check if the start cell (0, 0) is blocked
    if (grid[0][0] != 0) {
        printf("False\n");
    } else {
        // Start the search from (0, 0)
        dfs(0, 0);

        // Check if we found any treasures
        if (treasureCount == 0) {
            printf("False\n");
        } else {
            // --- THIS IS THE FIX ---
            // 1. Print "True" first.
            printf("True\n");

            // 2. Then loop and print all found treasures.
            for (int i = 0; i < treasureCount; i++) {
                // Using spaces as requested
                printf("%d %d %d\n", treasures[i].r, treasures[i].c, treasures[i].v);
            }
        }
    }
    // ---------------------

    // --- Free allocated memory ---
    for (int i = 0; i < N; i++) {
        free(grid[i]);
        free(visited[i]);
    }
    free(grid);
    free(visited);
    free(treasures);
    // -----------------------------

    return 0;
}