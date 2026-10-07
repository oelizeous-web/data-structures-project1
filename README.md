# Greedy Traffic Signal Control (Intersection Timing)

A Data Structures and Algorithms project that uses a **greedy algorithm** to decide which road gets the green light at a 4-way intersection, and for how long. It is written in both **Java** and **C**, and both versions behave the same way.

## The problem

An intersection has four roads: **North, South, East and West**. Only one road can have a green light at a time. Each time the light has to change, the controller must answer two questions:

1. Which road should go next?
2. How long should its green light last?

## The greedy idea

Every time the light changes, the program looks at all four roads and picks the one that is **most urgent right now**. It never goes back and changes an earlier decision. That "best choice for now" step is what makes the algorithm greedy.

**Urgency score of a road**

```
score = cars waiting + (seconds since the road's last green / 5)
```

- A long queue gives a high score, so busy roads are served first.
- The waiting-time part slowly raises the score of a road that has not had a green for a while. This stops a quiet road from being ignored forever (starvation).

**Green time**

```
green time = 2 seconds per waiting car
             (never less than 10 seconds, never more than 60 seconds)
```

## Files

| File | Description |
|------|-------------|
| `ArrayTraffic.java` | Java version |
| `ArrayTraffic.c` | C version |
| `README.md` | This file |

## How to run

**Java**

```
javac ArrayTraffic.java
java ArrayTraffic
```

**C**

```
gcc ArrayTraffic.c -o ArrayTraffic
./ArrayTraffic
```

On Windows, run the C program with `ArrayTraffic.exe` after compiling.

## Input

The program asks for the following. If you type something invalid, it asks again.

| Question | Allowed values |
|----------|----------------|
| Cars waiting now (for each of the 4 roads) | 0 to 200 |
| New cars per minute (for each of the 4 roads) | 0 to 30 |
| How many green lights to simulate | 1 to 30 |

## Sample run

Input: North 20 cars (6 per minute), South 8 (4), East 35 (9), West 4 (2), and 12 green lights.

```
Light#  Time(s)  Road    Queue  Green(s)  Cars passed
1       0        East    35     60        30
2       63       North   26     52        26
3       118      South   16     32        16
4       153      East    27     54        27
5       210      West    11     22        11
6       235      North   19     38        19
7       276      South   11     22        11
8       301      East    23     46        23
9       350      West    5      10        5
10      363      North   13     26        13
11      392      South   8      16        8
12      411      East    16     32        16

=== FINAL RESULTS (after 446 seconds) ===
North: 58 cars passed, 9 still waiting
South: 35 cars passed, 3 still waiting
East: 96 cars passed, 5 still waiting
West: 16 cars passed, 3 still waiting
Total cars passed : 205
Total still waiting: 20
```

East starts with the longest queue, so it gets the first (and longest) green. West is served only after its waiting time has raised its score.

## How the program is organised

| Part | What it does |
|------|--------------|
| `Road` (class in Java, struct in C) | Stores a road's name, cars waiting, arrival rate, waiting time and cars passed |
| `score` | Calculates how urgent a road is |
| `pickRoad` / `pick_road` | **The greedy choice:** finds the road with the highest score |
| `greenTime` / `green_time` | Works out the green time for the chosen road |
| `runGreenLight` / `run_green_light` | Lets cars pass, makes the other roads wait, and adds newly arriving cars |
| `readNumber` / `read_number` | Reads a number safely and repeats the question if the input is wrong |

## Settings you can change

These constants are at the top of each source file:

| Constant | Meaning | Default |
|----------|---------|---------|
| `SECONDS_PER_CAR` | Time for one car to pass | 2 |
| `MIN_GREEN` | Shortest green light (seconds) | 10 |
| `MAX_GREEN` | Longest green light (seconds) | 60 |
| `YELLOW_TIME` | Time lost when the light changes (seconds) | 3 |

## Complexity

Each decision checks 4 roads, so it takes O(n) time with n = 4. For R green lights the total is O(R x n), which is linear in the number of lights.

## Limitations

- Greedy gives a good result, but it is a heuristic. It is not proven to be the best possible timing.
- Only one road has green at a time. Real intersections often let opposite roads (for example North and South) go together.
- New cars arrive at a steady rate, rounded to whole cars.
- Cars take a fixed 2 seconds each to pass.
