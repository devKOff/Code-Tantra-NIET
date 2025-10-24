#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }

    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}