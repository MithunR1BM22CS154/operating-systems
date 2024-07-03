#include<stdio.h>

struct Process {
    int id;
    int priority;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
};

void priorityScheduling(struct Process[], int);

int main() {
    int n, i;
    float total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("\nEnter the details of processes:\n");
    for(i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d\n", i + 1);
        printf("Enter the priority: ");
        scanf("%d", &processes[i].priority);
        printf("Enter the burst time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].response_time = -1; // Initialize to -1 indicating not yet started
    }

    priorityScheduling(processes, n);

    printf("\nProcess\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].priority,
               processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time,
               processes[i].response_time);
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        total_response_time += processes[i].response_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
    printf("Average Response Time: %.2f\n", total_response_time / n);

    return 0;
}

void priorityScheduling(struct Process processes[], int n) {
    int i, j;
    struct Process temp;

    // Sort processes based on priority
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(processes[j].priority > processes[j+1].priority) {
                temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }

    int current_time = 0;
    for(i = 0; i < n; i++) {
        processes[i].waiting_time = current_time;
        processes[i].response_time = current_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        current_time += processes[i].burst_time;
    }
}
