#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct Process {
    int pid; // Process ID
    int burst_time; // Burst Time
    int arrival_time; // Arrival Time
};

// Function to sort processes by arrival time and burst time
void sortProcesses(struct Process proc[], int n) {
    int i, j;
    struct Process temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (proc[i].arrival_time > proc[j].arrival_time || 
               (proc[i].arrival_time == proc[j].arrival_time && proc[i].burst_time > proc[j].burst_time)) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate completion time, turnaround time, and waiting time
void calculateTimes(struct Process proc[], int n, int ct[], int tat[], int wt[]) {
    ct[0] = proc[0].burst_time + proc[0].arrival_time; // First process completion time
    
    for (int i = 1; i < n; i++) {
        if (proc[i].arrival_time > ct[i - 1]) {
            ct[i] = proc[i].arrival_time + proc[i].burst_time;
        } else {
            ct[i] = ct[i - 1] + proc[i].burst_time;
        }
    }

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - proc[i].arrival_time;
        wt[i] = tat[i] - proc[i].burst_time;
    }
}

// Function to display Gantt chart
void printGanttChart(struct Process proc[], int n, int ct[]) {
    printf("\nGantt Chart:\n");

    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < proc[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < proc[i].burst_time - 1; j++) printf(" ");
        printf("P%d", proc[i].pid);
        for (int j = 0; j < proc[i].burst_time - 1; j++) printf(" ");
        printf("|");
    }

    printf("\n ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < proc[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n");

    printf("0");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < proc[i].burst_time; j++) printf("  ");
        if (ct[i] > 9) printf("\b"); // Remove extra space for double digit numbers
        printf("%d", ct[i]);
    }
    printf("\n");
}

int main() {
    int n, arrival_times_given;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Are arrival times given? (1 for Yes, 0 for No): ");
    scanf("%d", &arrival_times_given);

    struct Process *proc = (struct Process *)malloc(n * sizeof(struct Process));
    int *ct = (int *)malloc(n * sizeof(int)); // Completion Time
    int *tat = (int *)malloc(n * sizeof(int)); // Turnaround Time
    int *wt = (int *)malloc(n * sizeof(int)); // Waiting Time

    // Input process IDs, arrival times, and burst times for each process
    for (int i = 0; i < n; i++) {
        printf("Enter process ID for process %d: ", i + 1);
        scanf("%d", &proc[i].pid);
        if (arrival_times_given) {
            printf("Enter arrival time for process %d: ", proc[i].pid);
            scanf("%d", &proc[i].arrival_time);
        } else {
            proc[i].arrival_time = 0;
        }
        printf("Enter burst time for process %d: ", proc[i].pid);
        scanf("%d", &proc[i].burst_time);
    }

    // Sort processes by arrival time and burst time
    sortProcesses(proc, n);

    // Calculate completion time, turnaround time, and waiting time
    calculateTimes(proc, n, ct, tat, wt);

    int total_wt = 0, total_tat = 0;
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time, ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);

    // Display Gantt chart
    printGanttChart(proc, n, ct);

    // Free allocated memory
    free(proc);
    free(ct);
    free(tat);
    free(wt);

    return 0;
}
