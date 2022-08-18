/*
 * Assignment 4
 * Developer: Dennis Dao
 * July 3, 2022
 * v1.0
 */

// Program to implement the priority scheduling algorithm, under the assumption all processes arrive at the SAME time
#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void enterInput(int *input, char* prompt); // Helper function for input

int main(void){
    // Variables
    int numProcesses;
    double avgWaitingTime = 0, avgCompletionTime = 0;
    char *msg1 = "Enter the number of processes (>0): "; // For specifying what user needs to input in the enterInput function
    char *msg2 = "Enter the burst time (>0): ";
    char *msg3 = "Enter the priority (>0): ";

    // Enter number of processes
    enterInput(&numProcesses, msg1);
    
    // Define id, burst time, priorities, and waiting time lists with a size equal to the amount of processes
    int burstTimes[numProcesses], pids[numProcesses], priorities[numProcesses], waitingTimes[numProcesses], completionTimes[numProcesses];
    printf("\n");

    // Enter burst times and priorites of process i
    for(int i = 0; i < numProcesses; i++){
        pids[i] = i+1;
        printf("For process[%d]:\n", pids[i]);
        // Enter burst times
        enterInput(&burstTimes[i], msg2);
        // Enter priorities
        enterInput(&priorities[i], msg3);
        printf("\n");
    }

    // Output process info for reference
    printf("The following has been input:\nPROCESS | BURST TIME | PRIORITY\n--------------------------------\n");
    for(int i = 0; i < numProcesses; i++){
        printf("%4d\t  %6d       %4d\n",pids[i], burstTimes[i], priorities[i]);
    }
    printf("\nThe priority scheduling algorithm will now be performed...\n\n");

    // Perform the scheduling algorithm
    // Sort by highest priority (lowest integer), will be indexed left to right so order must ascend
    for(int i = 0; i < numProcesses; i++){
        for(int j = 0; j < numProcesses - i - 1; j++){
            if(priorities[j] > priorities[j+1]){
                int temp;

                // Swap ids
                temp = pids[j];
                pids[j] = pids[j+1];
                pids[j+1] = temp;

                // Swap priorities
                temp = priorities[j];
                priorities[j] = priorities[j+1];
                priorities[j+1] = temp;

                // Swap bursts
                temp = burstTimes[j];
                burstTimes[j] = burstTimes[j+1];
                burstTimes[j+1] = temp;
            }
        }
    }

    // Determine waiting times and completion times
    for(int i = 0; i < numProcesses; i++){
        // If first process, no waiting, it is 1st in line
        // The completion time will be just the burst time
        if(i == 0){
            waitingTimes[i] = 0;
            completionTimes[i] = burstTimes[i];
        }
        else{
            // General formula - add the previous wait time with the previous burst time
            // The completion time will be the calculated waiting time plus the burst time
            waitingTimes[i] = waitingTimes[i-1] + burstTimes[i-1];
            completionTimes[i] = burstTimes[i] + waitingTimes[i];
        }
    }

    // Output process info, now with waiting time included
    printf("PROCESS | BURST TIME | PRIORITY | WAITING TIME | COMPLETION TIME\n-----------------------------------------------------------------\n");
    for(int i = 0; i < numProcesses; i++){
        printf("%4d\t  %6d       %4d\t     %4d\t%8d\n",pids[i], burstTimes[i], priorities[i], waitingTimes[i], completionTimes[i]);
    }
    printf("\n");

    // Calculate the average and output
    for(int i = 0; i < numProcesses; i++){
        avgWaitingTime += waitingTimes[i];
        avgCompletionTime += completionTimes[i];
    }
    avgWaitingTime /= numProcesses;
    avgCompletionTime /= numProcesses;
    printf("The final average waiting time is %f ms\n", avgWaitingTime);
    printf("The final average completion time is %f ms\n", avgCompletionTime);    
}

// Function definitions
// Helper function to get input
void enterInput(int *input, char* prompt){
    // For parsing the input
    char buffer[100];
    int ok = 0, temp;

    printf("%s", prompt);
    // Keep asking until a valid input
    while(!ok){
        fgets(buffer, sizeof(buffer), stdin);
        temp = atoi(buffer);

        // If 0 (intentionally or with non-integer) or negative, prompt the user again
        // The scheduling algorithm cannot be done with 0 or negative amounts of processes,
        // burst times, or priorities
        if(temp <= 0){
            puts("Invalid input. Try again.");
            printf("%s", prompt);
        }
        else{
            *input = temp;
            ok = 1;
        }
    }
}