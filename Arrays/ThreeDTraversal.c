#include <stdio.h>

int main(void) {
    int A[2][2][2] = {
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}}
    };

    printf("3D Array Traversal:\n");

    for (int i = 0; i < 2; i++) {
        printf("Layer %d:\n", i);

        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                printf("%d ", A[i][j][k]);
            }
            printf("\n");
        }
    }

    printf("Base address = %p\n",
           (void *)&A[0][0][0]);

    return 0;
}
