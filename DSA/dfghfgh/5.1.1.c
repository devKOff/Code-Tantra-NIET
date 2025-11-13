#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
struct Item {
    int value;
    int weight;
    double ratio; // Value-to-weight ratio
};

// Comparison function for sorting by ratio (descending order)
int compare(const void* a, const void* b) {
    struct Item* item1 = (struct Item*)a;
    struct Item* item2 = (struct Item*)b;
    if (item2->ratio < item1->ratio) return -1;
    if (item2->ratio > item1->ratio) return 1;
    return 0;
}

double fractionalKnapsack(int n, int W, struct Item arr[]) {
    // Sort items by value-to-weight ratio
    qsort(arr, n, sizeof(struct Item), compare);

    double totalValue = 0.0;
    int currWeight = 0;

    // Iterate through sorted items
    for (int i = 0; i < n; i++) {
        if (currWeight + arr[i].weight <= W) {
            // Take the whole item
            currWeight += arr[i].weight;
            totalValue += arr[i].value;
        } else {
            // Take a fraction of the item
            int remainingWeight = W - currWeight;
            double fraction = (double)remainingWeight / arr[i].weight;
            totalValue += fraction * arr[i].value;
            break; // Knapsack is full
        }
    }

    return totalValue;
}

int main() {
    int n, W;
    scanf("%d %d", &n, &W);

    struct Item arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].value, &arr[i].weight);
        arr[i].ratio = (double)arr[i].value / arr[i].weight; // Calculate ratio
    }

    double maxValue = fractionalKnapsack(n, W, arr);
    printf("%.6f\n", maxValue);

    return 0;
}