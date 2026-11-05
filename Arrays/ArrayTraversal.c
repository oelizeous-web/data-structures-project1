#include <stdio.h>

int main(void) {
    int A[] = {10, 20, 30, 40, 50};
    int n = sizeof(A) / sizeof(A[0]);

    printf("1D Array Traversal:\n");

    for (int i = 0; i < n; i++) {
        printf("A[%d] = %d\n", i, A[i]);
    }

    printf("Base address = %p\n", (void *)&A[0]);

    return 0;
}
