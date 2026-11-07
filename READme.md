# LPT Task Scheduler (C and Java)

Greedy scheduling of independent tasks on multiple identical processors, minimizing makespan using the **Longest Processing Time first (LPT)** rule.

## Problem

- **Independent tasks:** no task depends on another.
- **Identical processors:** every processor runs at the same speed.
- **Makespan:** the time at which the last processor finishes. The goal is to make this as small as possible.

## Algorithm

1. Sort tasks by duration, longest first.
2. For each task in that order, assign it to the processor with the smallest current load.
3. The makespan is the largest load across all processors.

LPT is not always optimal (the problem is NP-hard), but its makespan is provably within 4/3 of the optimum.

## Implementation notes
- The least-loaded processor is found with a linear scan, so assignment is O(n·m).
- Each task keeps its original ID, so the output shows the original task numbers.

## Files

| File | Description |
|------|-------------|
| `TaskScheduler.c` | C version (limits: 100 tasks, 20 processors, set by `#define`) |
| `TaskScheduler.java` | Java version |

## Build and run

gcc TaskScheduler.c -o lpt
./lpt
```

```
javac TaskScheduler.java
java TaskScheduler
```

Input: number of tasks, number of processors, then the task durations.

## Example

Input: 6 tasks, 2 processors, durations `7 5 4 3 2 2`

```
--- Schedule ---
Processor 1: T1(7) T4(3) T6(2) | load = 12
Processor 2: T2(5) T3(4) T5(2) | load = 11

Makespan = 12
```

`T1(7)` means original task 1 with duration 7.