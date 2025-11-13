#include <stdio.h>
#include <stdlib.h>

// Structure to represent a job
struct Job {
    int difficulty;
    int profit;
};

// Comparison function for sorting by profit (descending order)
int compare(const void* a, const void* b) {
    struct Job* job1 = (struct Job*)a;
    struct Job* job2 = (struct Job*)b;
    return job2->profit - job1->profit; // Sort by profit in descending order
}

long long maxProfit(int n, int m, struct Job jobs[], int workers[]) {
    // Sort jobs by profit in descending order
    qsort(jobs, n, sizeof(struct Job), compare);

    long long totalProfit = 0; // Use long long to handle large sums

    // For each worker
    for (int j = 0; j < m; j++) {
        int maxProfitForWorker = 0;
        // Find the best job this worker can do
        for (int i = 0; i < n; i++) {
            if (jobs[i].difficulty <= workers[j]) {
                maxProfitForWorker = jobs[i].profit;
                break; // Take the first (highest profit) feasible job
            }
        }
        totalProfit += maxProfitForWorker;
    }

    return totalProfit;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    struct Job jobs[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &jobs[i].difficulty);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &jobs[i].profit);
    }

    int workers[m];
    for (int j = 0; j < m; j++) {
        scanf("%d", &workers[j]);
    }

    long long result = maxProfit(n, m, jobs, workers);
    printf("%lld\n", result);

    return 0;
}