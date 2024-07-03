#include <stdio.h>

// Structure to hold process information
struct Process {
    int pid;        // Process ID
    int burst_time; // Burst time or execution time
    int deadline;   // Absolute deadline
};

// Function to perform earliest deadline scheduling
void earliestDeadlineFirst(struct Process processes[], int n) {
    // Sort processes based on deadline (ascending order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].deadline > processes[j + 1].deadline) {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    printf("Order of execution: ");

    // Traverse through sorted processes
    for (int i = 0; i < n; i++) {
        printf("%d ", processes[i].pid);
        current_time += processes[i].burst_time;

        // Check for deadline miss
        if (current_time > processes[i].deadline) {
            printf("(Deadline missed!) ");
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input burst times and deadlines for each process
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter deadline for process %d: ", i + 1);
        scanf("%d", &processes[i].deadline);
        processes[i].pid = i + 1; // Assigning process IDs sequentially
    }

    printf("\nEarliest Deadline First Scheduling\n");
    earliestDeadlineFirst(processes, n);

    return 0;
}
