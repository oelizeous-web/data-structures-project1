package Arrays;
public class ArrayTraversal {
    public static void main(String[] args) {
        int[] A = {10, 20, 30, 40, 50};

        System.out.println("1D Array Traversal:");

        for (int i = 0; i < A.length; i++) {
            System.out.println("A[" + i + "] = " + A[i]);
        }

        System.out.println(
            "Logical base address is the location of A[0]."
        );
    }
}
