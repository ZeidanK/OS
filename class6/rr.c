#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//dont forget to redo this
// Structure to represent a process
struct Process {
  int pid;             // Process ID
  int burst_time;      // Burst time (amount of CPU time needed)
  int remaining_time;  // Remaining burst time
  int turnaround_time; // Turnaround time
};

int main() {
  int num_processes, time_quantum;

  printf("Enter the number of processes: ");
  scanf("%d", &num_processes);

  printf("Enter the time quantum: ");
  scanf("%d", &time_quantum);

  // printf("Enter the turnaraound time: ");
  // scanf("%d", )
  struct Process processes[num_processes];

  // Get burst times for each process
  for (int i = 0; i < num_processes; i++) {
    processes[i].pid = i + 1;
    printf("Enter burst time for Process %d: ", i + 1);
    scanf("%d", &processes[i].burst_time);
    processes[i].remaining_time = processes[i].burst_time;
  }

  int time = 0;      // Current time
  int completed = 0; // Number of completed processes

  printf("\nRound Robin Scheduling:\n");

  while (completed < num_processes) {
    for (int i = 0; i < num_processes; i++) {
      if (processes[i].remaining_time > 0) {
        printf("Time %d: Process %d running\n", time, processes[i].pid);
        // add to the turnaround time for each process
        int time_to_add = 0;
        // Run the process for the time quantum or until completion
        if (processes[i].remaining_time <= time_quantum) {
          time_to_add = processes[i].remaining_time;
          time += processes[i].remaining_time;
          processes[i].remaining_time = 0;
          completed++;
        } else {
          time_to_add = time_quantum;
          time += time_quantum;
          processes[i].remaining_time -= time_quantum;
        }

        for (int j = 0; j < num_processes; j++) {
          if (processes[j].remaining_time > 0 && i != j) {
            processes[j].turnaround_time += time_to_add;
          }
        }

        // Sleep for a short duration to visualize the scheduling
        usleep(500000); // Sleep for 0.5 seconds (adjust as needed)
      }
    }
    // add a for loop to calculate the turnaround time for each process
  }
  // print the turnaround time for each process
  for (int i = 0; i < num_processes; i++) {
    printf("Process %d: Turnaround time = %d\n", processes[i].pid,
           processes[i].turnaround_time);
  }
  printf("All processes completed!\n");

  return 0;
}
