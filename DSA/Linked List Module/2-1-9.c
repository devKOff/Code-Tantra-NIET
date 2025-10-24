#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *midPoint(int N, char *Arr[], int ArrLen) {
    if (ArrLen == 0) {
        return NULL;
    }
    
    // The problem requires returning the first of the two middle elements for even length lists,
    // and the single middle element for odd length lists.
    // The index for this is mathematically represented by: floor((ArrLen - 1) / 2).
    // Standard integer division in C automatically computes the floor.
    int mid_index = (ArrLen - 1) / 2;
    
    return Arr[mid_index];
}

// Below functions are provided by the problem's environment for context and complete compilation.

int readStringArray(char *argsArray, char *arr[]) {
    int col = 0;
    char *token = strtok(argsArray, ",");
    while (token != NULL) {
        arr[col] = token;
        token = strtok(NULL, ",");
        col++;
    }
    return col;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        // Handle incorrect number of command-line arguments if needed for robustness
        return 1;
    }

    int N = atoi(argv[1]);
    char *Arr[strlen(argv[2])];
    int ArrLen = readStringArray(argv[2], Arr);
    
    printf("%s\n", midPoint(N, Arr, ArrLen));
    
    return 0;
}