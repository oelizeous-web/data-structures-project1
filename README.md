# Greedy Unit Fraction Decomposition (Egyptian Fractions)

A Data Structures and Algorithms project which **greedily decomposes a fraction into a sum of different unit fractions**. Available in **Java** and **C**; both do the same thing.

## The problem

A **unit fraction** has 1 as a numerator: 1/2, 1/3, 1/10. Any fraction smaller than 1 can be expressed as a sum of different unit fractions. Example:

```
5/6 = 1/2 + 1/3
```

This is a computational problem (no simulation).

## The greedy approach

At every step we take the **largest unit fraction that fits** into the remaining fraction and continue with the leftovers.

For the fraction n/d:

1. The largest unit fraction <= n/d is 1/k, where k = d / n rounded **up**.
    In the case above: d/n = 6/5 = 1.2, so k = 2 and we take 1/2
2. The leftovers are n/d - 1/k = (n*k - d) / (d*k), reduced by the gcd
3. Repeat until leftovers = 0.

The numerator will only get smaller with each step, hence the loop always terminates.

## Files

| File | Description |
|------|-------------|
| `UnitFraction.java` | Java implementation |
| `UnitFraction.c` | C implementation |
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

On Windows, use `UnitFraction.exe` after running the compilation.

## Input

The program asks for the following data. If the input is incorrect, it prompts the user again. After every result it asks if the user wants to decompose another fraction.

| Prompt | Valid values |
|--------|--------------|
| Numerator | 1 - 100 |
| Denominator | 2 - 1,000,000 (it must be greater than the numerator, since the fraction must be <1) |
| Decompose another fraction? | 1 = yes, 0 = no |

Fractions are simplified automatically, so 4/8 is treated as 1/2.

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

## Sample run with the number limit

Sometimes fractions lead to very rapidly increasing denominators. The program safely exits for 5/121, instead of giving a wrong result:
```
Step 1: 5/121  ->  take 1/25  ->  left over 4/3025
Step 2: 4/3025  ->  take 1/757  ->  left over 3/2289925
Step 3: 3/2289925  ->  take 1/763309  ->  left over 2/1747920361825

5/121 = 1/25 + 1/757 + 1/763309 + 2/1747920361825
(The next denominator would be too large for the computer to handle,
so the last part 2/1747920361825 couldn't be split further.)
```

## Program structure

| Part | Functionality |
|------|---------------|
| `gcd` | Computes greatest common divisor, needed for fractions' simplification |
| `readNumber` / `read_number` | Prompts the user for an integer safely; asks again if the value is incorrect |
| Greedy loop in `main` | Computes k, leftover fraction, reduces it and repeats |
| Overflow checking | Stops before a number gets too large for the computer to handle |

## Time complexity

There is one division, one multiplication and one gcd computation per step. The number of steps is bounded by the initial numerator; this is why the numerator is limited to 100.

## Limitations

- The greedy approach always terminates, but it **does not guarantee** the minimum number of steps or smallest possible denominators.
- Denominators may increase extremely rapidly. The program uses 64-bit integers (`long` in Java, `long long` in C); it safely stops before the next denominator would get too large and prints the unhandled part.
- Only proper fractions (<1) are accepted.
