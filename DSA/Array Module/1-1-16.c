#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 1 || n > 1000) {
        printf("-1\n");
        return 0;
    }

    getchar(); 

    char line[12000]; 
    if (fgets(line, sizeof(line), stdin) == NULL) {
        if (n > 0) printf("-1\n");
        return 0;
    }

    int arr[n];
    int count = 0;
    char *token;

    token = strtok(line, " \n");
    while (token != NULL && count < n) {
        arr[count] = atoi(token);
        count++;
        token = strtok(NULL, " \n");
    }

    if (token != NULL) {
        printf("-1\n");
        return 0;
    }

    if (count < n) {
        printf("-1\n");
        return 0;
    }

    int max = INT_MIN;
    int min = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    int range = max - min + 1;
    int *count_arr = calloc(range, sizeof(int));
    if (count_arr == NULL) {
        return 1; 
    }

    for (int i = 0; i < n; i++) {
        count_arr[arr[i] - min]++;
    }

    int k = 0;
    for (int i = 0; i < range; i++) {
        while (count_arr[i] > 0) {
            arr[k] = i + min;
            k++;
            count_arr[i]--;
        }
    }
    
    free(count_arr);

    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}