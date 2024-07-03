#include <stdio.h>

// Structure to hold process information
struct Process {
    int pid;        // Process ID
    int burst_time; // Burst time or execution time
    int remaining;  // Remaining burst time
};

// Function to perform round robin scheduling
void roundRobin(struct Process processes[], int n, int quantum) {
    int total_time = 0;
    int total_waiting_time = 0;

    // Initialize remaining time with burst time
    for (int i = 0; i < n; i++) {
        processes[i].remaining = processes[i].burst_time;
    }

    // Run until all processes are done
    while (1) {
        int done = 1;

        // Traverse all processes one by one repeatedly
        for (int i = 0; i < n; i++) {
            // If remaining burst time of a process is greater than 0,
            // then only need to process further
            if (processes[i].remaining > 0) {
                done = 0; // There is a pending process

                // If remaining burst time is greater than quantum,
                // process for quantum seconds and decrease remaining time by quantum
                if (processes[i].remaining > quantum) {
                    total_time += quantum;
                    processes[i].remaining -= quantum;
                } else { // If remaining burst time is smaller than or equal to quantum,
                    // process for remaining time
                    total_time += processes[i].remaining;
                    processes[i].remaining = 0;

                    // Calculate waiting time
                    int waiting_time = total_time - processes[i].burst_time;
                    total_waiting_time += waiting_time;

                    printf("Process %d completed. Waiting time: %d\n", processes[i].pid, waiting_time);
                }
            }
        }

        // If all processes are done
        if (done == 1) {
            break;
        }
    }

    // Calculate average waiting time
    float average_waiting_time = (float)total_waiting_time / n;
    printf("\nAverage waiting time: %.2f\n", average_waiting_time);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    int quantum;

    // Input burst times for each process
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].pid = i + 1; // Assigning process IDs sequentially
    }

    // Input quantum size
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    printf("\nRound Robin Scheduling\n\n");
    roundRobin(processes, n, quantum);

    return 0;
}
