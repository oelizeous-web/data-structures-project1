# Greedy Traffic Signal Control (Intersection Timing)

A Data Structures and Algorithms project, that applies a **greedy algorithm** to determine which road will get the green light at a 4-way intersection and for how long. It is implemented in both **Java** and **C** and behaves exactly the same in both.

## Problem statement

There is a set of 4 roads in an intersection: **North, South, East and West**. At any moment, only one road may have a green light. Each time the light needs to be changed, the controller needs to answer the following two questions:

1. Which road should have the light next?
2. How long should it have the green light?

## Greedy approach

Each time the light is about to be changed, the program checks all 4 roads and selects the one that is **the most urgent right now**. It never changes the decision afterwards. That "best choice right now" part makes the algorithm greedy.

**Urgency score of a road**

```
score = cars waiting + (seconds since the road's last green / 5)
```

- Longer queue results in higher score; therefore, the busier road is served first.
- Waiting time component gradually increases the urgency score of the road that hasn't got the green light for a while. This prevents a less busy road from being forgotten forever (starvation).

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

On Windows, run the C program using `ArrayTraffic.exe`.

## Input

The program asks for the following. If an invalid value is entered, it asks again.

| Question | Allowed values |
|----------|----------------|
| Cars waiting now (for each of the 4 roads) | 0 to 200 |
| New cars per minute (for each of the 4 roads) | 0 to 30 |
| How many green lights to simulate | 1 to 30 |

## Sample run

Input: North 20 cars (6 per minute), South 8 (4), East 35 (9), West 4 (2), 12 green lights.

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

East starts with the largest queue, and thus gets the first (and the largest) green light. The road West gets its turn only because its waiting time increased its urgency score.

## Program structure

| Module | Description |
|--------|-------------|
| `Road` (class in Java, struct in C) | Holds information about a road: its name, number of cars waiting, arrival rate, waiting time and number of cars passed |
| `score` | Calculating urgency score of the road |
| `pickRoad` / `pick_road` | **The greedy choice**: finding the most urgent road |
| `greenTime` / `green_time` | Calculating the green time for the selected road |
| `runGreenLight` / `run_green_light` | Allowing cars to pass, making other roads wait and adding new arrivals |
| `readNumber` / `read_number` | Safe number reading and asking the question again on invalid input |

## Adjustable settings

These constants are defined at the beginning of each source file:

| Constant | Meaning | Default |
|----------|---------|---------|
| `SECONDS_PER_CAR` | Time required to pass one car (seconds) | 2 |
| `MIN_GREEN` | Minimal green light (seconds) | 10 |
| `MAX_GREEN` | Maximal green light (seconds) | 60 |
| `YELLOW_TIME` | Time lost due to the light changing (seconds) | 3 |

## Complexity

Checking each road takes O(n) with n=4, therefore the complexity of a decision is O(n). For R green lights total complexity is O(R x n), which is linear in terms of number of lights.

## Limitations

- Greedy algorithm gives good results but is just a heuristic. There is no proof of it being the optimal solution.
- Only one road has green light at a time. In reality, traffic lights allow opposite roads (e.g. North and South) to go at once.
- New cars arrive with constant rate, rounded to the nearest integer.
- Cars pass the road in a fixed amount of 2 seconds each.
