#include <stdio.h>

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
} Process;

void sort_by_arrival_time(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void round_robin_scheduling(Process processes[], int n, int time_slice) {
    int time = 0;
    int completed = 0;
    int gantt_chart[1000]; // Assume a maximum of 1000 time units for simplicity
    int gantt_index = 0;
    int time_in_chart[1000]; // Track the times for the Gantt chart

    while (completed < n) {
        int all_done = 1; // Flag to check if all processes are done

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= time) {
                all_done = 0; // At least one process is not done

                time_in_chart[gantt_index] = time;

                if (processes[i].remaining_time <= time_slice) {
                    time += processes[i].remaining_time;
                    gantt_chart[gantt_index++] = processes[i].id;
                    processes[i].remaining_time = 0;
                    processes[i].completion_time = time;
                    completed++;
                } else {
                    time += time_slice;
                    gantt_chart[gantt_index++] = processes[i].id;
                    processes[i].remaining_time -= time_slice;
                }
            } else if (processes[i].arrival_time > time) {
                time = processes[i].arrival_time;
            }
        }

        if (all_done) {
            break;
        }
    }

    // Print Gantt chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gantt_index; i++) {
        printf(" P%d |", gantt_chart[i]);
    }
    printf("\n%d", time_in_chart[0]);
    for (int i = 1; i < gantt_index; i++) {
        printf("    %d", time_in_chart[i]);
    }
    printf("    %d\n", time); // Print final time
}

void calculate_turnaround_time(Process processes[], int n, int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = processes[i].completion_time - processes[i].arrival_time;
    }
}

void calculate_waiting_time(Process processes[], int n, int waiting_time[]) {
    for (int i = 0; i < n; i++) {
        waiting_time[i] = processes[i].completion_time - processes[i].arrival_time - processes[i].burst_time;
    }
}

int main() {
    int n, time_slice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];
    
    for (int i = 0; i < n; i++) {
        printf("Enter process ID, arrival time, and burst time for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].id, &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    printf("Enter the time slice: ");
    scanf("%d", &time_slice);
    
    sort_by_arrival_time(processes, n);
    round_robin_scheduling(processes, n, time_slice);
    
    int turnaround_time[n], waiting_time[n];
    calculate_turnaround_time(processes, n, turnaround_time);
    calculate_waiting_time(processes, n, waiting_time);

    // Calculate average turnaround time and waiting time
    float total_turnaround_time = 0, total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += turnaround_time[i];
        total_waiting_time += waiting_time[i];
    }
    float avg_turnaround_time = total_turnaround_time / n;
    float avg_waiting_time = total_waiting_time / n;
    
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                processes[i].id, 
                processes[i].arrival_time, 
                processes[i].burst_time, 
                processes[i].completion_time, 
                turnaround_time[i], 
                waiting_time[i]);
    }

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    
    return 0;
}
