#include <stdio.h>

int main() {
    int r, c;
    scanf("%d %d", &r, &c);

    int matrix[r][c];
    int non_zero_count = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] != 0) {
                non_zero_count++;
            }
        }
    }

    int total_elements = r * c;
    int zero_count = total_elements - non_zero_count;

    if (zero_count > non_zero_count) {
        printf("True\n");
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (matrix[i][j] != 0) {
                    printf("%d %d %d\n", i, j, matrix[i][j]);
                }
            }
        }
    } else {
        printf("False\n");
    }

    return 0;
}