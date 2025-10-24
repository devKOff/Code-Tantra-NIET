#include <stdio.h>

int main() {
    int r, c;
    scanf("%d %d", &r, &c);

    int matrix[r][c];
    int zero_count = 0;
    int non_zero_count = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] == 0) {
                zero_count++;
            } else {
                non_zero_count++;
            }
        }
    }

    int total_elements = r * c;

    if (zero_count > total_elements / 2) {
        if (non_zero_count == 0) {
            printf("-1\n");
        } else {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (matrix[i][j] != 0) {
                        printf("%d %d %d\n", i, j, matrix[i][j]);
                    }
                }
            }
        }
    } else {
        printf("-1\n");
    }

    return 0;
}