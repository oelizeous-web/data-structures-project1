#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 128   /* must be >= 2 x digits of the largest input */
#define BASE 10

// 1. Data Structure
// A big number is a fixed array of digits, least-significant digit first.
typedef struct {
    int digits[MAX_DIGITS];
    int length;
} BigNumber;

// 2. Helper Operations
static BigNumber make_zero(void) {
    BigNumber z = {{0}, 1};
    return z;
}

static void normalize(BigNumber* n) {          // drop leading zeros
    while (n->length > 1 && n->digits[n->length - 1] == 0) n->length--;
}

static BigNumber from_string(const char* s) {
    BigNumber n = make_zero();
    int len = (int)strlen(s);
    n.length = len;
    for (int i = 0; i < len; i++) n.digits[i] = s[len - 1 - i] - '0';
    normalize(&n);
    return n;
}

static void print_number(BigNumber n) {
    for (int i = n.length - 1; i >= 0; i--) putchar('0' + n.digits[i]);
    putchar('\n');
}

// Takes digits [lo, hi) of n as a new number
static BigNumber slice(BigNumber n, int lo, int hi) {
    BigNumber r = make_zero();
    if (lo >= n.length) return r;
    if (hi > n.length) hi = n.length;
    r.length = hi - lo;
    for (int i = lo; i < hi; i++) r.digits[i - lo] = n.digits[i];
    normalize(&r);
    return r;
}

static BigNumber add(BigNumber a, BigNumber b) {
    BigNumber r = make_zero();
    int n = a.length > b.length ? a.length : b.length, carry = 0;
    for (int i = 0; i < n; i++) {
        int s = carry + (i < a.length ? a.digits[i] : 0) + (i < b.length ? b.digits[i] : 0);
        r.digits[i] = s % BASE;
        carry = s / BASE;
    }
    r.length = n;
    if (carry) {
        if (n >= MAX_DIGITS) { printf("Increase MAX_DIGITS\n"); exit(1); }
        r.digits[n] = carry;
        r.length = n + 1;
    }
    return r;
}

// Multiply by BASE^k (append k zeros at the low end)
static BigNumber shift(BigNumber a, int k) {
    if (a.length == 1 && a.digits[0] == 0) return a;
    if (a.length + k > MAX_DIGITS) { printf("Increase MAX_DIGITS\n"); exit(1); }
    BigNumber r = make_zero();
    for (int i = 0; i < a.length; i++) r.digits[i + k] = a.digits[i];
    r.length = a.length + k;
    return r;
}

// 3. Divide and Conquer Logic (4 recursive multiplications)
static BigNumber multiply(BigNumber a, BigNumber b) {
    int n = a.length > b.length ? a.length : b.length;

    // CONQUER Phase: Base Case (both numbers are single digits)
    if (n == 1) {
        int p = a.digits[0] * b.digits[0];
        BigNumber r = make_zero();
        r.digits[0] = p % BASE;
        r.digits[1] = p / BASE;
        r.length = 2;
        normalize(&r);
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

int main() {
    char x[65], y[65];
    printf("Enter first number: ");
    scanf("%64s", x);
    printf("Enter second number: ");
    scanf("%64s", y);
    printf("%s x %s = ", x, y);
    print_number(multiply(from_string(x), from_string(y)));
    return 0;
}