import java.util.Scanner;

/*
 * GREEDY ALGORITHM: Unit Fraction Decomposition (Egyptian Fractions)
 *
 * A UNIT FRACTION has 1 on top, like 1/2, 1/3 or 1/10.
 * Goal: write any fraction as a sum of DIFFERENT unit fractions.
 *      Example:  5/6 = 1/2 + 1/3
 *
 * GREEDY IDEA: at every step, take the BIGGEST unit fraction that still
 * fits inside what is left. Then repeat with the leftover part.
 *
 * Fraction n/d  ->  the biggest unit fraction not larger than it is 1/k,
 *      where k = d / n rounded UP     (example: 5/6 -> 6/5 = 1.2 -> k = 2)
 * Leftover = n/d - 1/k = (n*k - d) / (d*k)    (then simplified)
 *
 * The top number (numerator) gets smaller every step, so the loop must finish.
 */
public class UnitFraction {

    static final int MAX_TERMS = 100;                    // numerator <= 100 means at most 100 terms
    static final long MAX_SAFE = 4000000000000000000L;   // stop before numbers get too big for a long

    // Greatest common divisor (used to simplify fractions)
    static long gcd(long a, long b) {
        while (b != 0) {
            long temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    // Keeps asking until the user types a whole number between min and max
    static long readNumber(Scanner input, String question, long min, long max) {
        while (true) {
            System.out.print(question);
            if (input.hasNextLong()) {
                long value = input.nextLong();
                if (value >= min && value <= max) {
                    return value;
                }
            } else {
                input.next();   // throw away the wrong input
            }
            System.out.println("  Please enter a number from " + min + " to " + max + ".");
        }
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        long[] denominators = new long[MAX_TERMS];   // the k of each unit fraction 1/k
        int again = 1;

        System.out.println("=== GREEDY UNIT FRACTION DECOMPOSITION ===");

        while (again == 1) {
            // 1. Get the fraction from the user
            System.out.println();
            long top = readNumber(input, "Numerator (1-100): ", 1, 100);
            long bottom = readNumber(input, "Denominator (2-1000000): ", 2, 1000000);
            while (top >= bottom) {
                System.out.println("  The fraction must be less than 1, so the denominator must be bigger.");
                bottom = readNumber(input, "Denominator (2-1000000): ", 2, 1000000);
            }

            // simplify first, e.g. 4/8 becomes 1/2
            long g = gcd(top, bottom);
            long n = top / g;
            long d = bottom / g;
            System.out.println();
            System.out.println("Decomposing " + n + "/" + d + ":");

            // 2. The greedy loop
            int count = 0;
            boolean tooBig = false;
            while (n != 0) {
                long k = (d + n - 1) / n;       // d / n rounded up

                if (k > MAX_SAFE / d) {         // the next number would be too big
                    tooBig = true;
                    break;
                }

                long newN = n * k - d;          // leftover fraction
                long newD = d * k;
                long common = gcd(newN, newD);
                newN = newN / common;
                newD = newD / common;

                denominators[count] = k;
                count++;
                System.out.println("Step " + count + ": " + n + "/" + d
                        + "  ->  take 1/" + k + "  ->  left over " + newN + "/" + newD);

                n = newN;
                d = newD;
            }

            // 3. Show the answer
            System.out.println();
            System.out.print(top + "/" + bottom + " = ");
            for (int i = 0; i < count; i++) {
                if (i > 0) {
                    System.out.print(" + ");
                }
                System.out.print("1/" + denominators[i]);
            }
            if (tooBig) {
                System.out.println(" + " + n + "/" + d);
                System.out.println("(The next denominator is too large for the computer to store,");
                System.out.println(" so the last part " + n + "/" + d + " could not be split further.)");
            } else {
                System.out.println();
                System.out.println("Number of unit fractions used: " + count);
            }

            again = (int) readNumber(input, "\nDecompose another fraction? (1 = yes, 0 = no): ", 0, 1);
        }
        System.out.println("Goodbye!");
    }
}
