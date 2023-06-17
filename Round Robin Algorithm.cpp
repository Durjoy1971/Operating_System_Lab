#include <bits/stdc++.h>
using namespace std;

#define MAX_PROCESSES 10

struct Process {
    int pid;
    int burst_time;
    int remaining_time;
};

void roundRobin(struct Process processes[], int n, int time_quantum) {
    int completed = 0;
    int current_time = 0;

    // Create an array to store the Gantt chart
    int gantt_chart[MAX_PROCESSES * time_quantum];

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time <= time_quantum) {
                    int execution_time = processes[i].remaining_time;
                    current_time += execution_time;
                    processes[i].remaining_time = 0;
                    printf("Process %d executed for %d units.\n", processes[i].pid, processes[i].burst_time);
                    printf("Process %d completed.\n", processes[i].pid);
                    completed++;

                    // Store the execution in the Gantt chart
                    for (int j = 0; j < execution_time; j++) {
                        gantt_chart[current_time - execution_time + j] = processes[i].pid;
                    }
                } else {
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                    printf("Process %d executed for %d units.\n", processes[i].pid, time_quantum);

                    // Store the execution in the Gantt chart
                    for (int j = 0; j < time_quantum; j++) {
                        gantt_chart[current_time - time_quantum + j] = processes[i].pid;
                    }
                }
            }
        }
    }

    // Print the Gantt chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < current_time; i++) {
        printf("%d ", gantt_chart[i]);
    }
    printf("\n");
}

int main() {
    struct Process processes[MAX_PROCESSES];
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\nRound Robin Scheduling:\n");
    roundRobin(processes, n, time_quantum);

    return 0;
}