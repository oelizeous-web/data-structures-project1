package Arrays;
public class ThreeDTraversal {
    public static void main(String[] args) {
        int[][][] A = {
            {{1, 2}, {3, 4}},
            {{5, 6}, {7, 8}}
        };

        System.out.println("3D Array Traversal:");

        for (int i = 0; i < A.length; i++) {
            System.out.println("Layer " + i + ":");

            for (int j = 0; j < A[i].length; j++) {
                for (int k = 0; k < A[i][j].length; k++) {
                    System.out.print(A[i][j][k] + " ");
                }
                System.out.println();
            }
        }

        System.out.println(
            "Logical base element is A[0][0][0]."
        );
    }
}
