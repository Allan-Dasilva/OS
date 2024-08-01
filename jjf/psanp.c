#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id;
    int burst_time;
    int priority;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void findWaitingAndTurnaroundTime(struct Process proc[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < proc[i].arrival_time) {
            current_time = proc[i].arrival_time;
        }
        proc[i].waiting_time = current_time - proc[i].arrival_time;
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
        proc[i].completion_time = current_time + proc[i].burst_time;
        current_time = proc[i].completion_time;
    }
}

void sortProcesses(struct Process proc[], int n, bool has_arrival_time) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (has_arrival_time) {
                if (proc[i].arrival_time > proc[j].arrival_time || 
                    (proc[i].arrival_time == proc[j].arrival_time && proc[i].priority > proc[j].priority)) {
                    struct Process temp = proc[i];
                    proc[i] = proc[j];
                    proc[j] = temp;
                }
            } else {
                if (proc[i].priority > proc[j].priority) {
                    struct Process temp = proc[i];
                    proc[i] = proc[j];
                    proc[j] = temp;
                }
            }
        }
    }
}

void priorityScheduling(struct Process proc[], int n, bool has_arrival_time) {
    sortProcesses(proc, n, has_arrival_time);
    findWaitingAndTurnaroundTime(proc, n);

    int total_waiting_time = 0, total_turnaround_time = 0;

    printf("\nProcesses\tBurst Time\tPriority\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burst_time, proc[i].priority, proc[i].arrival_time, proc[i].waiting_time, proc[i].turnaround_time, proc[i].completion_time);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_turnaround_time / n);

    // Constructing Gantt chart with idle times
    printf("\n\nGantt Chart:\n");
    int last_completion_time = 0;
    printf("|");
    for (int i = 0; i < n; i++) {
        if (proc[i].arrival_time > last_completion_time) {
            printf(" Idle |");
            printf("  P%d  |", proc[i].id);
        } else {
            printf("  P%d  |", proc[i].id);
        }
        last_completion_time = proc[i].completion_time;
    }
    printf("\n0");

    last_completion_time = 0;
    for (int i = 0; i < n; i++) {
        if (proc[i].arrival_time > last_completion_time) {
            printf("\t%d", proc[i].arrival_time);
        }
        printf("\t%d", proc[i].completion_time);
        last_completion_time = proc[i].completion_time;
    }
    printf("\n");
}

int main() {
    int n;
    bool has_arrival_time;

    printf("Consider arrival times? (1 for Yes, 0 for No): ");
    scanf("%d", &has_arrival_time);

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        if (has_arrival_time) {
            printf("Enter process ID, burst time, priority, and arrival time for process %d: ", i + 1);
            scanf("%d %d %d %d", &proc[i].id, &proc[i].burst_time, &proc[i].priority, &proc[i].arrival_time);
        } else {
            printf("Enter process ID, burst time, and priority for process %d: ", i + 1);
            scanf("%d %d %d", &proc[i].id, &proc[i].burst_time, &proc[i].priority);
            proc[i].arrival_time = 0; // Default arrival time if not considered
        }
    }

    priorityScheduling(proc, n, has_arrival_time);

    return 0;
}
