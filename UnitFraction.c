#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100
#define MAX_SAFE 4000000000000000000LL

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

long long read_number(const char *question, long long min, long long max) {
    char buffer[128];
    char *end = NULL;

    while (1) {
        printf("%s", question);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nNo more input. Program stopped.\n");
            exit(0);
        }

        errno = 0;
        long long value = strtoll(buffer, &end, 10);

        if (end == buffer || errno == ERANGE) {
            printf("  Please enter a number from %lld to %lld.\n", min, max);
            continue;
        }

        while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
            end++;
        }

        if (*end != '\0') {
            printf("  Please enter a number from %lld to %lld.\n", min, max);
            continue;
        }

        if (value >= min && value <= max) {
            return value;
        }

        printf("  Please enter a number from %lld to %lld.\n", min, max);
    }
}

int main(void) {
    long long denominators[MAX_TERMS];
    int again = 1;

    printf("=== GREEDY UNIT FRACTION DECOMPOSITION ===\n");

    while (again == 1) {
        printf("\n");
        long long top = read_number("Numerator (1-100): ", 1, 100);
        long long bottom = read_number("Denominator (2-1000000): ", 2, 1000000);

        while (top >= bottom) {
            printf("  The fraction must be less than 1, so the denominator must be bigger.\n");
            bottom = read_number("Denominator (2-1000000): ", 2, 1000000);
        }

        long long g = gcd(top, bottom);
        long long n = top / g;
        long long d = bottom / g;
        printf("\nDecomposing %lld/%lld:\n", n, d);

        int count = 0;
        int too_big = 0;

        while (n != 0) {
            long long k = (d + n - 1) / n;

            if (k > MAX_SAFE / d) {
                too_big = 1;
                break;
            }

            long long new_n = n * k - d;
            long long new_d = d * k;
            long long common = gcd(new_n, new_d);
            new_n /= common;
            new_d /= common;

            denominators[count++] = k;
            printf("Step %d: %lld/%lld  ->  take 1/%lld  ->  left over %lld/%lld\n",
                   count, n, d, k, new_n, new_d);

            n = new_n;
            d = new_d;
        }

        printf("\n%lld/%lld = ", top, bottom);
        for (int i = 0; i < count; i++) {
            if (i > 0) {
                printf(" + ");
            }
            printf("1/%lld", denominators[i]);
        }

        if (too_big) {
            printf(" + %lld/%lld\n", n, d);
            printf("(The next denominator is too large for the computer to store,\n");
            printf(" so the last part %lld/%lld could not be split further.)\n", n, d);
        } else {
            printf("\nNumber of unit fractions used: %d\n", count);
        }

        again = (int) read_number("\nDecompose another fraction? (1 = yes, 0 = no): ", 0, 1);
    }

    printf("Goodbye!\n");
    return 0;
}
