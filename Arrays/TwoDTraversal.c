#include <stdio.h>

int main(void) {
    int A[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    printf("2D Array Traversal:\n");

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("Base address = %p\n",
           (void *)&A[0][0]);

    return 0;
}
