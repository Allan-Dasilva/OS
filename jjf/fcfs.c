#include <stdio.h>

// Define a structure for processes
struct Process {
    int id;
    int burst_time;
    int arrival_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

// Function to sort processes by arrival time
void sortByArrivalTime(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void fcfs(struct Process processes[], int n) {
    int total_idle_time = 0; // Initialize total idle time
    int current_time = 0; // Track the current time
   
    // Calculate completion time for each process
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    current_time = processes[0].completion_time;
    for (int i = 1; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            total_idle_time += processes[i].arrival_time - current_time;
            current_time = processes[i].arrival_time;
        }
        processes[i].completion_time = current_time + processes[i].burst_time;
        current_time = processes[i].completion_time;
    }
   
    // Calculate turnaround time and waiting time for each process
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
   
    // Displaying the Gantt chart and process details
    printf("Gantt Chart:\n");
    printf("|");
    int last_completion_time = 0;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time > last_completion_time) {
            printf(" Idle |");
            last_completion_time = processes[i].arrival_time;
        }
        printf(" P%d |", processes[i].id);
        last_completion_time = processes[i].completion_time;
    }
    printf("\n");
    printf("0");
    last_completion_time = 0;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time > last_completion_time) {
            printf("\t %d", processes[i].arrival_time);
            last_completion_time = processes[i].arrival_time;
        }
        printf("\t %d", processes[i].completion_time);
        last_completion_time = processes[i].completion_time;
    }
    printf("\n\n");
   
    printf("Process\tBurstTime\tArrivalTime\tCompletionTime\tWaiting Time\tTurnaroundTime\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t\t%d\t\t\t%d\n",
               processes[i].id, processes[i].burst_time, processes[i].arrival_time, processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
   
    // Calculating average waiting time and average turnaround time
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
   
    float average_waiting_time = (float) total_waiting_time / n;
    float average_turnaround_time = (float) total_turnaround_time / n;
   
    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
    printf("Total Idle Time: %d\n", total_idle_time);
}

int main() {
    int n, arrival_time_given;
    printf("Enter number of processes: ");
    scanf("%d", &n);
   
    struct Process processes[n];
    int default_arrival_time = 0;

    // Asking user whether arrival times are provided or not
    printf("Are arrival times provided for all processes? (1 for Yes, 0 for No): ");
    scanf("%d", &arrival_time_given);
   
    if (arrival_time_given) {
        // Inputting burst times and arrival times accordingly
        for (int i = 0; i < n; i++) {
            printf("Enter process ID for process %d: ", i + 1);
            scanf("%d", &processes[i].id);
            printf("Enter burst time for process P%d: ", processes[i].id);
            scanf("%d", &processes[i].burst_time);
            printf("Enter arrival time for process P%d: ", processes[i].id);
            scanf("%d", &processes[i].arrival_time);
        }
    } else {
        // Inputting burst times without arrival times
        for (int i = 0; i < n; i++) {
            printf("Enter process ID for process %d: ", i + 1);
            scanf("%d", &processes[i].id);
            printf("Enter burst time for process P%d: ", processes[i].id);
            scanf("%d", &processes[i].burst_time);
            processes[i].arrival_time = default_arrival_time; // Default arrival time is 0
        }
    }
   
    // Sort processes by arrival time
    sortByArrivalTime(processes, n);
   
    // Calling FCFS function with input data
    fcfs(processes, n);
   
    return 0;
}
