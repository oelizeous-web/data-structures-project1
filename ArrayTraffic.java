import java.util.Scanner;

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
public class ArrayTraffic {

    static final int NUM_ROADS = 4;
    static final int SECONDS_PER_CAR = 2;   // one car passes every 2 seconds
    static final int MIN_GREEN = 10;        // shortest green light (seconds)
    static final int MAX_GREEN = 60;        // longest green light (seconds)
    static final int YELLOW_TIME = 3;       // time lost when the light changes

    // Information stored about one road
    static class Road {
        String name;
        int carsWaiting;        // cars in the queue now
        int arrivalsPerMinute;  // new cars arriving every minute
        int secondsSinceGreen;  // how long this road has been waiting
        int carsPassed;         // total cars that have gone through
    }

    // ---------- Reading input safely ----------
    // Keeps asking until the user types a whole number between min and max
    static int readNumber(Scanner input, String question, int min, int max) {
        while (true) {
            System.out.print(question);
            if (input.hasNextInt()) {
                int value = input.nextInt();
                if (value >= min && value <= max) {
                    return value;
                }
            } else {
                input.next();   // throw away the wrong input
            }
            System.out.println("  Please enter a number from " + min + " to " + max + ".");
        }
    }

    // ---------- The greedy part ----------
    // Score of a road: higher score = more urgent
    static int score(Road r) {
        return r.carsWaiting + r.secondsSinceGreen / 5;
    }

    // GREEDY CHOICE: find the road with the highest score
    static int pickRoad(Road[] roads) {
        int best = 0;
        for (int i = 1; i < NUM_ROADS; i++) {
            if (score(roads[i]) > score(roads[best])) {
                best = i;
            }
        }
        return best;
    }

    // How many seconds of green does this road get?
    static int greenTime(Road r) {
        int seconds = r.carsWaiting * SECONDS_PER_CAR;
        if (seconds < MIN_GREEN) {
            seconds = MIN_GREEN;
        }
        if (seconds > MAX_GREEN) {
            seconds = MAX_GREEN;
        }
        return seconds;
    }

    // ---------- Running one green light ----------
    // Gives green to roads[chosen] and updates every road. Returns cars that passed.
    static int runGreenLight(Road[] roads, int chosen, int green) {
        int totalTime = green + YELLOW_TIME;
        int passed = 0;

        for (int i = 0; i < NUM_ROADS; i++) {
            if (i == chosen) {
                // cars that CAN pass during the green light
                int canPass = green / SECONDS_PER_CAR;
                if (canPass > roads[i].carsWaiting) {
                    canPass = roads[i].carsWaiting;   // not more than the queue
                }
                roads[i].carsWaiting = roads[i].carsWaiting - canPass;
                roads[i].carsPassed = roads[i].carsPassed + canPass;
                roads[i].secondsSinceGreen = 0;
                passed = canPass;
            } else {
                roads[i].secondsSinceGreen = roads[i].secondsSinceGreen + totalTime;
            }

            // new cars arrive on EVERY road while time passes (rounded to nearest whole car)
            int newCars = (roads[i].arrivalsPerMinute * totalTime + 30) / 60;
            roads[i].carsWaiting = roads[i].carsWaiting + newCars;
        }
        return passed;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        Road[] roads = new Road[NUM_ROADS];
        String[] names = {"North", "South", "East", "West"};

        System.out.println("=== GREEDY TRAFFIC LIGHT CONTROL ===");
        System.out.println();

        // 1. Get the data from the user
        for (int i = 0; i < NUM_ROADS; i++) {
            roads[i] = new Road();
            roads[i].name = names[i];
            System.out.println("Road: " + names[i]);
            roads[i].carsWaiting = readNumber(input, "  Cars waiting now (0-200): ", 0, 200);
            roads[i].arrivalsPerMinute = readNumber(input, "  New cars per minute (0-30): ", 0, 30);
        }
        int cycles = readNumber(input, "How many green lights to simulate (1-30)? ", 1, 30);

        // 2. Run the simulation
        System.out.println();
        System.out.println("Light#  Time(s)  Road    Queue  Green(s)  Cars passed");
        int time = 0;
        for (int light = 1; light <= cycles; light++) {
            int chosen = pickRoad(roads);              // greedy choice
            int green = greenTime(roads[chosen]);
            int queueBefore = roads[chosen].carsWaiting;

            int passed = runGreenLight(roads, chosen, green);

            System.out.printf("%-7d %-8d %-7s %-6d %-9d %d%n",
                    light, time, roads[chosen].name, queueBefore, green, passed);
            time = time + green + YELLOW_TIME;
        }

        // 3. Show the results
        System.out.println();
        System.out.println("=== FINAL RESULTS (after " + time + " seconds) ===");
        int totalPassed = 0;
        int totalWaiting = 0;
        for (int i = 0; i < NUM_ROADS; i++) {
            System.out.println(roads[i].name + ": " + roads[i].carsPassed
                    + " cars passed, " + roads[i].carsWaiting + " still waiting");
            totalPassed = totalPassed + roads[i].carsPassed;
            totalWaiting = totalWaiting + roads[i].carsWaiting;
        }
        System.out.println("Total cars passed : " + totalPassed);
        System.out.println("Total still waiting: " + totalWaiting);
    }
}
