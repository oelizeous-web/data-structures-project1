import java.util.Scanner;

public class MultiplicationDivideConquer {

    static final int MAX_DIGITS = 128;   // must be >= 2 x digits of the largest input
    static final int BASE = 10;

    // 1. Data Structure
    // A big number is a fixed array of digits, least-significant digit first.
    static class BigNumber {
        int[] digits = new int[MAX_DIGITS];
        int length = 1;

        static BigNumber fromString(String s) {
            BigNumber n = new BigNumber();
            n.length = s.length();
            for (int i = 0; i < s.length(); i++) n.digits[i] = s.charAt(s.length() - 1 - i) - '0';
            n.normalize();
            return n;
        }

        void normalize() {               // drop leading zeros
            while (length > 1 && digits[length - 1] == 0) length--;
        }

        boolean isZero() { return length == 1 && digits[0] == 0; }

        @Override
        public String toString() {
            StringBuilder sb = new StringBuilder();
            for (int i = length - 1; i >= 0; i--) sb.append(digits[i]);
            return sb.toString();
        }
    }

    // 2. Helper Operations

    // Takes digits [lo, hi) of n as a new number
    static BigNumber slice(BigNumber n, int lo, int hi) {
        BigNumber r = new BigNumber();
        if (lo >= n.length) return r;
        hi = Math.min(hi, n.length);
        r.length = hi - lo;
        for (int i = lo; i < hi; i++) r.digits[i - lo] = n.digits[i];
        r.normalize();
        return r;
    }

    static BigNumber add(BigNumber a, BigNumber b) {
        BigNumber r = new BigNumber();
        int n = Math.max(a.length, b.length), carry = 0;
        for (int i = 0; i < n; i++) {
            int s = carry + (i < a.length ? a.digits[i] : 0) + (i < b.length ? b.digits[i] : 0);
            r.digits[i] = s % BASE;
            carry = s / BASE;
        }
        r.length = n;
        if (carry > 0) {
            if (n >= MAX_DIGITS) throw new IllegalStateException("Increase MAX_DIGITS");
            r.digits[n] = carry;
            r.length = n + 1;
        }
        return r;
    }

    // Multiply by BASE^k (append k zeros at the low end)
    static BigNumber shift(BigNumber a, int k) {
        if (a.isZero()) return a;
        if (a.length + k > MAX_DIGITS) throw new IllegalStateException("Increase MAX_DIGITS");
        BigNumber r = new BigNumber();
        for (int i = 0; i < a.length; i++) r.digits[i + k] = a.digits[i];
        r.length = a.length + k;
        return r;
    }

    // 3. Divide and Conquer Logic (4 recursive multiplications)
    static BigNumber multiply(BigNumber a, BigNumber b) {
        int n = Math.max(a.length, b.length);

        // CONQUER Phase: Base Case (both numbers are single digits)
        if (n == 1) {
            int p = a.digits[0] * b.digits[0];
            BigNumber r = new BigNumber();
            r.digits[0] = p % BASE;
            r.digits[1] = p / BASE;
            r.length = 2;
            r.normalize();
            return r;
        }

        // DIVIDE Phase: a = a1*10^m + a0,  b = b1*10^m + b0
        int m = n / 2;
        BigNumber a0 = slice(a, 0, m), a1 = slice(a, m, n);
        BigNumber b0 = slice(b, 0, m), b1 = slice(b, m, n);

        // CONQUER Phase: all four sub-products
        BigNumber ac = multiply(a1, b1);
        BigNumber ad = multiply(a1, b0);
        BigNumber bc = multiply(a0, b1);
        BigNumber bd = multiply(a0, b0);

        // COMBINE Phase: ac*10^(2m) + (ad + bc)*10^m + bd
        BigNumber middle = add(ad, bc);
        return add(add(shift(ac, 2 * m), shift(middle, m)), bd);
    }

    public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    System.out.print("Enter first number: ");
    String x = scan.next();
    System.out.print("Enter second number: ");
    String y = scan.next();
    System.out.println(x + " x " + y + " = "
        + multiply(BigNumber.fromString(x), BigNumber.fromString(y)));
}
}