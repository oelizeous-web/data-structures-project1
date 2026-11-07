package TaskProcessing;

import java.util.Scanner;

public class TaskScheduling {

    static class Task {
        int id;        // original task number (1-based)
        int duration;

        Task(int id, int duration) {
            this.id = id;
            this.duration = duration;
        }
    }

    // Insertion sort, longest duration first. Sorts the objects so IDs travel along.
    static void sortDescending(Task[] tasks) {
        for (int i = 1; i < tasks.length; i++) {
            Task key = tasks[i];
            int j = i - 1;
            while (j >= 0 && tasks[j].duration < key.duration) {
                tasks[j + 1] = tasks[j];
                j--;
            }
            tasks[j + 1] = key;
        }
    }

    // Linear scan: index of the processor with the smallest current load.
    static int leastLoaded(int[] load) {
        int best = 0;
        for (int p = 1; p < load.length; p++) {
            if (load[p] < load[best]) best = p;
        }
        return best;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Number of tasks: ");
        int n = sc.nextInt();
        System.out.print("Number of processors: ");
        int m = sc.nextInt();

        if (n < 1 || m < 1) {
            System.out.println("Invalid input.");
            return;
        }

        Task[] tasks = new Task[n];
        System.out.println("Enter " + n + " task durations:");
        for (int i = 0; i < n; i++) {
            tasks[i] = new Task(i + 1, sc.nextInt());
        }

        sortDescending(tasks);

        int[] load = new int[m];
        int[] assigned = new int[n];   // assigned[i] = processor for sorted task i

        for (int i = 0; i < n; i++) {
            int p = leastLoaded(load);
            load[p] += tasks[i].duration;
            assigned[i] = p;
        }

        int makespan = 0;
        System.out.println("\n--- Schedule ---");
        for (int p = 0; p < m; p++) {
            System.out.print("Processor " + (p + 1) + ": ");
            for (int i = 0; i < n; i++) {
                if (assigned[i] == p)
                    System.out.print("T" + tasks[i].id + "(" + tasks[i].duration + ") ");
            }
            System.out.println("| load = " + load[p]);
            if (load[p] > makespan) makespan = load[p];
        }
        System.out.println("\nMakespan = " + makespan);
        sc.close();
    }
}