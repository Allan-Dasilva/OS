#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int priority;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    bool is_completed;
};

void sortProcesses(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival_time > proc[j + 1].arrival_time || 
                (proc[j].arrival_time == proc[j + 1].arrival_time && proc[j].priority > proc[j + 1].priority)) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

void prioritySchedulingWithPreemption(struct Process proc[], int n) {
    int current_time = 0, completed = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;
    int last_process_id = -1;

    printf("\nGantt Chart:\n|");
    while (completed != n) {
        int min_priority_index = -1;
        int min_priority = 100000;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && !proc[i].is_completed) {
                if (proc[i].priority < min_priority || 
                    (proc[i].priority == min_priority && proc[i].arrival_time < proc[min_priority_index].arrival_time)) {
                    min_priority = proc[i].priority;
                    min_priority_index = i;
                }
            }
        }

        if (min_priority_index != -1) {
            if (last_process_id != proc[min_priority_index].id) {
                printf(" %d | P%d |", current_time, proc[min_priority_index].id);
                last_process_id = proc[min_priority_index].id;
            }

            proc[min_priority_index].remaining_time--;

            if (proc[min_priority_index].remaining_time == 0) {
                proc[min_priority_index].is_completed = true;
                proc[min_priority_index].completion_time = current_time + 1;
                proc[min_priority_index].turnaround_time = proc[min_priority_index].completion_time - proc[min_priority_index].arrival_time;
                proc[min_priority_index].waiting_time = proc[min_priority_index].turnaround_time - proc[min_priority_index].burst_time;

                total_waiting_time += proc[min_priority_index].waiting_time;
                total_turnaround_time += proc[min_priority_index].turnaround_time;
                completed++;
            }
        } else {
            if (last_process_id != -1) {
                printf(" %d | Idle |", current_time);
                last_process_id = -1;
            }
        }
        current_time++;
    }
    printf(" %d |\n", current_time);

    printf("\nProcesses\tBurst Time\tPriority\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burst_time, proc[i].priority, proc[i].arrival_time, proc[i].waiting_time, proc[i].turnaround_time, proc[i].completion_time);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_turnaround_time / n);
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
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].is_completed = false;
    }

    // Sort processes based on arrival time and priority
    sortProcesses(proc, n);

    prioritySchedulingWithPreemption(proc, n);

    return 0;
}
