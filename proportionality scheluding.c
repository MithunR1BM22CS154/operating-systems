#include <stdio.h>

// Structure to hold process information
struct Process {
    int pid;        // Process ID
    int burst_time; // Burst time or execution time
    int weight;     // Weight of the process
};

// Function to perform Weighted Round Robin scheduling
void weightedRoundRobin(struct Process processes[], int n) {
    int total_time = 0;
    int total_waiting_time = 0;

    // Find the total weight of all processes
    int total_weight = 0;
    for (int i = 0; i < n; i++) {
        total_weight += processes[i].weight;
    }

    // Run until all processes are done
    while (1) {
        int done = 1;

        // Traverse all processes one by one
        for (int i = 0; i < n; i++) {
            // If remaining burst time of a process is greater than 0,
            // then only need to process further
            if (processes[i].burst_time > 0) {
                done = 0; // There is a pending process

                // Calculate time quantum for this process based on its weight
                float quantum = (float)processes[i].weight / total_weight;

                // If remaining burst time is greater than quantum,
                // process for quantum seconds and decrease remaining time by quantum
                if (processes[i].burst_time > quantum) {
                    total_time += quantum;
                    processes[i].burst_time -= quantum;
                } else { // If remaining burst time is smaller than or equal to quantum,
                    // process for remaining time
                    total_time += processes[i].burst_time;
                    processes[i].burst_time = 0;

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

    // Input burst times and weights for each process
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter weight for process %d: ", i + 1);
        scanf("%d", &processes[i].weight);
        processes[i].pid = i + 1; // Assigning process IDs sequentially
    }

    printf("\nWeighted Round Robin Scheduling\n\n");
    weightedRoundRobin(processes, n);

    return 0;
}
