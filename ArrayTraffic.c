#include <stdio.h>
#include <string.h>

/*
 * GREEDY ALGORITHM: Traffic Light Timing at an Intersection
 *
 * An intersection has 4 roads: North, South, East, West.
 * Only ONE road can have a green light at a time.
 *
 * GREEDY IDEA: every time the light must change, look at all roads
 * and pick the one that is MOST URGENT right now (best choice for now).
 * We never go back and change a past decision.
 *
 * How urgent is a road?
 *      score = cars waiting + (seconds since its last green / 5)
 * The second part makes sure a road with few cars is not ignored forever.
 *
 * Green time = 2 seconds per waiting car, but never less than 10 seconds
 * and never more than 60 seconds.
 */

#define NUM_ROADS 4
#define SECONDS_PER_CAR 2   /* one car passes every 2 seconds */
#define MIN_GREEN 10        /* shortest green light (seconds) */
#define MAX_GREEN 60        /* longest green light (seconds) */
#define YELLOW_TIME 3       /* time lost when the light changes */

/* Information stored about one road */
typedef struct {
    char name[10];
    int cars_waiting;         /* cars in the queue now */
    int arrivals_per_minute;  /* new cars arriving every minute */
    int seconds_since_green;  /* how long this road has been waiting */
    int cars_passed;          /* total cars that have gone through */
} Road;

/* ---------- Reading input safely ---------- */
/* Keeps asking until the user types a whole number between min and max */
int read_number(const char* question, int min, int max) {
    int value;
    while (1) {
        printf("%s", question);
        fflush(stdout);

        if (scanf("%d", &value) == 1) {
            if (value >= min && value <= max) {
                return value;
            }
        } else {
            /* throw away the wrong input (letters, symbols...) */
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            if (c == EOF) {
                printf("\nNo more input. Program stopped.\n");
                return min;
            }
        }

        /* remove any extra text still left in the input buffer */
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }

        printf("  Please enter a number from %d to %d.\n", min, max);
    }
}

/* ---------- The greedy part ---------- */
/* Score of a road: higher score = more urgent */
int score(Road r) {
    return r.cars_waiting + r.seconds_since_green / 5;
}

/* GREEDY CHOICE: find the road with the highest score */
int pick_road(Road roads[]) {
    int best = 0;
    for (int i = 1; i < NUM_ROADS; i++) {
        if (score(roads[i]) > score(roads[best])) {
            best = i;
        }
    }
    return best;
}

/* How many seconds of green does this road get? */
int green_time(Road r) {
    int seconds = r.cars_waiting * SECONDS_PER_CAR;
    if (seconds < MIN_GREEN) {
        seconds = MIN_GREEN;
    }
    if (seconds > MAX_GREEN) {
        seconds = MAX_GREEN;
    }
    return seconds;
}

/* ---------- Running one green light ---------- */
/* Gives green to roads[chosen] and updates every road. Returns cars that passed. */
int run_green_light(Road roads[], int chosen, int green) {
    int total_time = green + YELLOW_TIME;
    int passed = 0;

    for (int i = 0; i < NUM_ROADS; i++) {
        if (i == chosen) {
            /* cars that CAN pass during the green light */
            int can_pass = green / SECONDS_PER_CAR;
            if (can_pass > roads[i].cars_waiting) {
                can_pass = roads[i].cars_waiting;   /* not more than the queue */
            }
            roads[i].cars_waiting = roads[i].cars_waiting - can_pass;
            roads[i].cars_passed = roads[i].cars_passed + can_pass;
            roads[i].seconds_since_green = 0;
            passed = can_pass;
        } else {
            roads[i].seconds_since_green = roads[i].seconds_since_green + total_time;
        }

        /* new cars arrive on EVERY road while time passes (rounded to nearest whole car) */
        int new_cars = (roads[i].arrivals_per_minute * total_time + 30) / 60;
        roads[i].cars_waiting = roads[i].cars_waiting + new_cars;
    }
    return passed;
}

int main() {
    Road roads[NUM_ROADS] = {0};
    const char* names[NUM_ROADS] = {"North", "South", "East", "West"};

    printf("=== GREEDY TRAFFIC LIGHT CONTROL ===\n\n");

    /* 1. Get the data from the user */
    for (int i = 0; i < NUM_ROADS; i++) {
        strcpy(roads[i].name, names[i]);
        printf("Road: %s\n", names[i]);
        roads[i].cars_waiting = read_number("  Cars waiting now (0-200): ", 0, 200);
        roads[i].arrivals_per_minute = read_number("  New cars per minute (0-30): ", 0, 30);
    }
    int cycles = read_number("How many green lights to simulate (1-30)? ", 1, 30);

    /* 2. Run the simulation */
    printf("\nLight#  Time(s)  Road    Queue  Green(s)  Cars passed\n");
    int time = 0;
    for (int light = 1; light <= cycles; light++) {
        int chosen = pick_road(roads);              /* greedy choice */
        int green = green_time(roads[chosen]);
        int queue_before = roads[chosen].cars_waiting;

        int passed = run_green_light(roads, chosen, green);

        printf("%-7d %-8d %-7s %-6d %-9d %d\n",
               light, time, roads[chosen].name, queue_before, green, passed);
        time = time + green + YELLOW_TIME;
    }

    /* 3. Show the results */
    printf("\n=== FINAL RESULTS (after %d seconds) ===\n", time);
    int total_passed = 0;
    int total_waiting = 0;
    for (int i = 0; i < NUM_ROADS; i++) {
        printf("%s: %d cars passed, %d still waiting\n",
               roads[i].name, roads[i].cars_passed, roads[i].cars_waiting);
        total_passed = total_passed + roads[i].cars_passed;
        total_waiting = total_waiting + roads[i].cars_waiting;
    }
    printf("Total cars passed : %d\n", total_passed);
    printf("Total still waiting: %d\n", total_waiting);

    return 0;
}
