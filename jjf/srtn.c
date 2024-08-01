#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 10
#define MAX_TIME 1000  // Assuming 1000 time units is sufficient

typedef struct {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
    int startTime;
    int endTime;
    int restartTime; // Added to track when a process is restarted
} Process;

// Function to swap two processes
void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes by arrival time
void sortByArrivalTime(Process processes[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                swap(&processes[i], &processes[j]);
            }
        }
    }
}

// Function to calculate waiting times, turn around times, completion times, and start/stop times
void calculateTimes(Process processes[], int n, int ganttChart[], int *length) {
    int time = 0, completed = 0, i;
    int minIndex;
    int minRemainingTime;
    int isCompleted[MAX_PROCESSES] = {0};
    int currentProcess = -1;
    
    // Initialize Gantt Chart
    for (i = 0; i < MAX_TIME; i++) {
        ganttChart[i] = -1;
    }

    while (completed < n) {
        minRemainingTime = INT_MAX;
        minIndex = -1;

        // Find the process with the minimum remaining time that has arrived
        for (i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && !isCompleted[i] && processes[i].remainingTime < minRemainingTime) {
                minRemainingTime = processes[i].remainingTime;
                minIndex = i;
            }
        }

        if (minIndex != -1) {
            if (currentProcess != minIndex) {
                if (currentProcess != -1) {
                    processes[currentProcess].endTime = time;
                    printf("Process %d stops at time %d\n", processes[currentProcess].id, time);
                }
                currentProcess = minIndex;
                if (processes[currentProcess].startTime == -1) {
                    processes[currentProcess].startTime = time;
                    printf("Process %d starts at time %d\n", processes[currentProcess].id, time);
                } else {
                    processes[currentProcess].restartTime = time;
                    printf("Process %d resumes at time %d\n", processes[currentProcess].id, time);
                }
            }
            processes[minIndex].remainingTime--;
            ganttChart[time] = processes[minIndex].id;
            if (processes[minIndex].remainingTime == 0) {
                processes[minIndex].completionTime = time + 1;
                processes[minIndex].turnAroundTime = processes[minIndex].completionTime - processes[minIndex].arrivalTime;
                processes[minIndex].waitingTime = processes[minIndex].turnAroundTime - processes[minIndex].burstTime;
                isCompleted[minIndex] = 1;
                processes[minIndex].endTime = time + 1;
                printf("Process %d stops at time %d\n", processes[minIndex].id, time + 1);
                completed++;
            }
        } else {
            if (currentProcess != -1) {
                printf("Process %d stops at time %d\n", currentProcess, time);
                currentProcess = -1;
            }
            ganttChart[time] = -1; // No process running
        }
        time++;
    }
    
    // Determine the actual length of Gantt chart used
    *length = time;
}

void printGanttChart(int ganttChart[], int length, Process processes[], int n) {
    printf("\nGantt Chart:\n");
    int i;
    int currentProcess = -1;
    int startTime = 0;

    // Print the Gantt chart
    for (i = 0; i < length; i++) {
        if (ganttChart[i] != -1) {
            if (currentProcess != ganttChart[i]) {
                if (currentProcess != -1) {
                    printf("(%d, %d) ", startTime, i);
                }
                currentProcess = ganttChart[i];
                startTime = i;
                printf("P%d ", currentProcess);
            }
        } else {
            if (currentProcess != -1) {
                printf("(%d, %d) ", startTime, i);
                currentProcess = -1;
            }
            printf("| ");
        }
    }
    // Print the final segment if it exists
    if (currentProcess != -1) {
        printf("(%d, %d) ", startTime, length);
    }
    printf("\n");

    printf("\n");

    // Print start, restart, and end times
    printf("\nProcess ID   Start Time   Restart Time   End Time\n");
    for (i = 0; i < n; i++) {
        if (processes[i].endTime != 0) {
            printf("   %d            %d            %d           %d\n",
                   processes[i].id, processes[i].startTime,
                   (processes[i].restartTime == -1 ? 0 : processes[i].restartTime),
                   processes[i].endTime);
        }
    }
}

int main() {
    Process processes[MAX_PROCESSES];
    int n, i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter process ID, arrival time, and burst time for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].id, &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;  // Initialize remaining time
        processes[i].startTime = -1;  // Initialize start time
        processes[i].endTime = 0;     // Initialize end time
        processes[i].restartTime = -1; // Initialize restart time
    }

    // Sort processes by arrival time
    sortByArrivalTime(processes, n);

    // Create an array to store Gantt Chart
    int ganttChart[MAX_TIME] = {0}; // Assuming 1000 time units is sufficient
    int length = 0;
    calculateTimes(processes, n, ganttChart, &length);

    // Print the Gantt Chart and Start/End Times
    printGanttChart(ganttChart, length, processes, n);

    printf("\nProcess ID   Burst Time   Arrival Time   Waiting Time   Turn-Around Time   Completion Time\n");
    for (i = 0; i < n; i++) {
        printf("   %d            %d            %d              %d                 %d                 %d\n",
               processes[i].id, processes[i].burstTime, processes[i].arrivalTime,
               processes[i].waitingTime, processes[i].turnAroundTime, processes[i].completionTime);
    }

    return 0;
}
