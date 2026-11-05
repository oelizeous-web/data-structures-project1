package Arrays;
public class TwoDTraversal {
    public static void main(String[] args) {
        int[][] A = {
            {1, 2, 3},
            {4, 5, 6}
        };

        System.out.println("2D Array Traversal:");

        for (int i = 0; i < A.length; i++) {
            for (int j = 0; j < A[i].length; j++) {
                System.out.print(A[i][j] + " ");
            }
            System.out.println();
        }

        System.out.println(
            "Logical base element is A[0][0]."
        );
    }
}
