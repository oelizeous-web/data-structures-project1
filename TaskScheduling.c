#include <stdio.h>

#define MAX_TASKS 100
#define MAX_PROCS 20

typedef struct {
    int id;        /* original task number (1-based) */
    int duration;
} Task;

/* Insertion sort, longest duration first. Sorts the whole record so IDs travel along. */
void sortDescending(Task tasks[], int n) {
    for (int i = 1; i < n; i++) {
        Task key = tasks[i];
        int j = i - 1;
        while (j >= 0 && tasks[jcd cd].duration < key.duration) {
            tasks[j + 1] = tasks[j];
            j--;
        }
        tasks[j + 1] = key;
    }
}

/* Linear scan: index of the processor with the smallest current load. */
int leastLoaded(int load[], int m) {
    int best = 0;
    for (int p = 1; p < m; p++) {
        if (load[p] < load[best]) best = p;
    }
    return best;
}

int main(void) {
    int n, m;
    Task tasks[MAX_TASKS];
    int load[MAX_PROCS] = {0};
    int assigned[MAX_TASKS];   /* assigned[i] = processor for sorted task i */

    printf("Number of tasks: ");
    scanf("%d", &n);
    printf("Number of processors: ");
    scanf("%d", &m);

    if (n < 1 || n > MAX_TASKS || m < 1 || m > MAX_PROCS) {
        printf("Invalid input (tasks 1-%d, processors 1-%d).\n", MAX_TASKS, MAX_PROCS);
        return 1;
    }

    printf("Enter %d task durations:\n", n);
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        scanf("%d", &tasks[i].duration);
    }

    sortDescending(tasks, n);

    for (int i = 0; i < n; i++) {
        int p = leastLoaded(load, m);
        load[p] += tasks[i].duration;
        assigned[i] = p;
    }

    int makespan = 0;
    printf("\n--- Schedule ---\n");
    for (int p = 0; p < m; p++) {
        printf("Processor %d: ", p + 1);
        for (int i = 0; i < n; i++) {
            if (assigned[i] == p)
                printf("T%d(%d) ", tasks[i].id, tasks[i].duration);
        }
        printf("| load = %d\n", load[p]);
        if (load[p] > makespan) makespan = load[p];
    }
    printf("\nMakespan = %d\n", makespan);
    return 0;
}