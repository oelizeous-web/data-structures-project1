# Greedy Unit Fraction Decomposition (Egyptian Fractions)

A Data Structures and Algorithms project that uses a **greedy algorithm** to write a fraction as a sum of different **unit fractions**. It is written in both **Java** and **C**, and both versions behave the same way.

## The problem

A **unit fraction** has 1 on top, such as 1/2, 1/3 or 1/10. Any fraction smaller than 1 can be written as a sum of different unit fractions. For example:

```
5/6 = 1/2 + 1/3
```

This is a purely computational problem (not a real-life simulation).

## The greedy idea

At every step, take the **biggest unit fraction that still fits** inside what is left, then repeat with the leftover.

For a fraction `n/d`:

1. The biggest unit fraction not larger than `n/d` is `1/k`, where `k = d / n` rounded **up**.
   Example: for 5/6, d/n = 6/5 = 1.2, so k = 2 and we take 1/2.
2. The leftover is `n/d - 1/k = (n*k - d) / (d*k)`, simplified with the gcd (greatest common divisor).
3. Repeat until the leftover is 0.

The numerator gets smaller at every step, so the loop always finishes.

## Files

| File | Description |
|------|-------------|
| `UnitFraction.java` | Java version |
| `UnitFraction.c` | C version |
| `README.md` | This file |

## How to run

**Java**

```
javac UnitFraction.java
java UnitFraction
```

**C**

```
gcc UnitFraction.c -o UnitFraction
./UnitFraction
```

On Windows, run the C program with `UnitFraction.exe` after compiling.

## Input

The program asks for the following. If you type something invalid, it asks again. After each result it asks whether you want to decompose another fraction.

| Question | Allowed values |
|----------|----------------|
| Numerator | 1 to 100 |
| Denominator | 2 to 1,000,000 (must be bigger than the numerator, because the fraction must be less than 1) |
| Decompose another fraction? | 1 = yes, 0 = no |

The fraction is simplified first, so 4/8 is treated as 1/2.

## Sample run

Input: numerator 3, denominator 7.

```
Decomposing 3/7:
Step 1: 3/7  ->  take 1/3  ->  left over 2/21
Step 2: 2/21  ->  take 1/11  ->  left over 1/231
Step 3: 1/231  ->  take 1/231  ->  left over 0/1

3/7 = 1/3 + 1/11 + 1/231
Number of unit fractions used: 3
```

## Sample with the number limit

Some fractions make the denominators grow very fast. For 5/121 the program stops safely instead of giving a wrong answer:

```
Step 1: 5/121  ->  take 1/25  ->  left over 4/3025
Step 2: 4/3025  ->  take 1/757  ->  left over 3/2289925
Step 3: 3/2289925  ->  take 1/763309  ->  left over 2/1747920361825

5/121 = 1/25 + 1/757 + 1/763309 + 2/1747920361825
(The next denominator is too large for the computer to store,
 so the last part 2/1747920361825 could not be split further.)
```

## How the program is organised

| Part | What it does |
|------|--------------|
| `gcd` | Finds the greatest common divisor, used to simplify fractions |
| `readNumber` / `read_number` | Reads a number safely and repeats the question if the input is wrong |
| Greedy loop in `main` | Finds `k`, computes the leftover fraction, simplifies it and repeats |
| Overflow check | Stops before a number becomes too big for the computer to store |

## Complexity

Each step does one division, one multiplication and one gcd calculation. The number of steps is at most the starting numerator, which is why the numerator is limited to 100.

## Limitations

- Greedy always finishes, but it does **not** always give the shortest answer or the smallest denominators.
- Denominators can grow extremely fast. The program uses 64-bit numbers (`long` in Java, `long long` in C), so it stops when the next denominator would be too large and prints the part it could not split.
- Only proper fractions (less than 1) are accepted.
