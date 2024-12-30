#include <stdio.h>
#include <setjmp.h>

jmp_buf env1, env2, env3;
int process1_done = 0, process2_done = 0, process3_done = 0;
int env1_set = 0, env2_set = 0, env3_set = 0;

// Function to print PCB status with simulated PID and address info
void printPCB(const char* processName, const char* state) {
    printf("PCB Status - %s | State: %s |\n", 
           processName, state);
}

void process1() {
    int pid = 1001;  // Simulated PID for process1
    printf("Process 1: Execution started (PID %d, Address: %p)\n", pid, &env1);
    printPCB("Process 1", "Running");

    if (setjmp(env1) == 0) {
        // Save state and simulate interruption
        printf("Process 1: Interrupted - Reason: I/O request sent\n");
        printPCB("Process 1", "Waiting (I/O Interrupt)");
        if (env2_set) longjmp(env2, 1);  // Switch to process 2 if env2 is set
    } else {
        // Resuming process 1 after process 2 completes
        printf("Process 1: Resuming execution(PID %d, Address: %p)\n", pid, &env1);
        printf("Process 1: Finishing execution\n");
        process1_done = 1;
        printPCB("Process 1", "Terminated");
    }
}

void process2() {
    int pid = 1002;  // Simulated PID for process2
    printf("Process 2: Starting execution (PID %d, Address: %p)\n", pid, &env2);
    printPCB("Process 2", "Running");

    printf("Process 2: In progress\n");
    printf("Process 2: Finishing execution\n");
    process2_done = 1;
    printPCB("Process 2", "Terminated");

    if (env1_set) longjmp(env1, 1);  // Switch back to process 1 if env1 is set
}

void process3() {
    int pid = 1003;  // Simulated PID for process3 (highest priority)
    printf("Process 3: Execution started (PID %d, Address: %p)\n", pid, &env3);
    printPCB("Process 3", "Running");

    printf("Process 3: In progress\n");
    printf("Process 3: Finishing execution\n");
    process3_done = 1;
    printPCB("Process 3", "Terminated");

    // Start Process 1 after Process 3 completes
    if (env1_set) longjmp(env1, 1);
}

int main() {
    printf("Context switching\n");
    printf("Context switching is the process of saving the state of a currently running task\n");
    printf("or process and loading the state of another, allowing multiple processes to share the \n");
    printf("CPU effectively.It enables multitasking by switching between tasks.This switching \n");
    printf("involves storing and restoring registers, program counters, and memory maps, allowing t\n");
    printf("he operating system to manage execution efficiently across different processes.\n");
    printf(" ");
    printf("\nMain: Setting up initial states and priorities.\n");

    // Print initial process priorities and simulated PIDs
    printf("Process Priorities:\n");
    printf("Priority 1: Process 3, PID 1003\n");
    printf("Priority 2: Process 1, PID 1001\n");
    printf("Priority 3: Process 2, PID 1002\n\n");

    // Set up Process 3 (highest priority)
    if (setjmp(env3) == 0) {
        env3_set = 1;  // Mark env3 as initialized
        process3();
    }

    // Set up Process 1 after Process 3 completes
    if (process3_done && setjmp(env1) == 0) {
        env1_set = 1;  // Mark env1 as initialized
        process1();
    }

    // Set up Process 2 to run after an I/O interruption occurs in Process 1
    if (process3_done && !process1_done && setjmp(env2) == 0) {
        env2_set = 1;  // Mark env2 as initialized
        process2();
    }

    return 0;
}
