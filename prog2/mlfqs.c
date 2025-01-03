#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include "prioque.h"

// Constants for quantum and demotion/promotion counters at each priority level
#define Q_L1 10
#define B_L1 1
#define G_L1 -1  // Infinite

#define Q_L2 30
#define B_L2 2
#define G_L2 1

#define Q_L3 100
#define B_L3 2
#define G_L3 2

#define Q_L4 200
#define B_L4 -1  // Infinite
#define G_L4 2

// Struct for each behavior phase of a process
typedef struct {
    uint64_t cpuburst;
    uint64_t ioburst;
} ProcessBehavior;

// Struct for each process
typedef struct {
    int32_t pid;
    uint64_t arrival_time;
    Queue behaviors; // Queue of ProcessBehavior
    uint64_t remaining_burst;
    uint64_t remaining_io;
    int level;
    int b_count;
    int g_count;
    bool completed;
} Process;

Queue L1, L2, L3, L4, ArrivalQ;
Process null_process = {.pid = -1, .completed = true};

// Function prototypes
void initialize_queues();
void enqueue_process(Process *p);
void dequeue_process(Process *p);
void handle_promotion_demotion(Process *p);
void execute_process(Process *p, int *cpu_usage, int *clock);
void advance_to_next_phase(Process *p);
void read_process_input();

void initialize_queues() {
    init_queue(&L1, sizeof(Process), true, NULL, true);
    init_queue(&L2, sizeof(Process), true, NULL, true);
    init_queue(&L3, sizeof(Process), true, NULL, true);
    init_queue(&L4, sizeof(Process), true, NULL, true);
    init_queue(&ArrivalQ, sizeof(Process), true, NULL, true);
}

void enqueue_process(Process *p) {
    if (p->level == 1) {
        add_to_queue(&L1, p, INT32_MAX - p->arrival_time);
    } else if (p->level == 2) {
        add_to_queue(&L2, p, INT32_MAX - p->arrival_time);
    } else if (p->level == 3) {
        add_to_queue(&L3, p, INT32_MAX - p->arrival_time);
    } else if (p->level == 4) {
        add_to_queue(&L4, p, INT32_MAX - p->arrival_time);
    }
}

void dequeue_process(Process *p) {
    if (p->level == 1) {
        delete_from_queue(&L1, p);
    } else if (p->level == 2) {
        delete_from_queue(&L2, p);
    } else if (p->level == 3) {
        delete_from_queue(&L3, p);
    } else if (p->level == 4) {
        delete_from_queue(&L4, p);
    }
}

void execute_process(Process *p, int *cpu_usage, int *clock) {
    if (p->completed) return;

    int quantum = (p->level == 1 ? Q_L1 : (p->level == 2 ? Q_L2 : (p->level == 3 ? Q_L3 : Q_L4)));
    int ticks = 0;

    printf("RUN: Process %d started execution from level %d at time %d; wants to execute for %" PRIu64 " ticks.\n", p->pid, p->level, *clock, p->remaining_burst);
    while (ticks < quantum && p->remaining_burst > 0) {
        ticks++;
        (*clock)++;
        (*cpu_usage)++;
        p->remaining_burst--;
    }

    if (p->remaining_burst == 0) {
        if (p->remaining_io > 0) {
            printf("I/O: Process %d blocked for I/O at time %d.\n", p->pid, *clock);
            (*clock) += p->remaining_io;
            p->remaining_io = 0;
            advance_to_next_phase(p);
        } else {
            advance_to_next_phase(p);
        }
    } else {
        printf("QUEUED: Process %d queued at level %d at time %d.\n", p->pid, p->level, *clock);
        enqueue_process(p);
    }

    handle_promotion_demotion(p);
}

void advance_to_next_phase(Process *p) {
    ProcessBehavior b;
    if (remove_from_front(&p->behaviors, &b)) {
        p->remaining_burst = b.cpuburst;
        p->remaining_io = b.ioburst;
        p->b_count = 0;
        p->g_count = 0;
    } else {
        p->completed = true;
        destroy_queue(&p->behaviors);
        printf("FINISHED: Process %d finished at time %d.\n", p->pid, p->arrival_time);
    }
}

void handle_promotion_demotion(Process *p) {
    if (p->remaining_burst > 0) {
        p->b_count++;
        if ((p->level == 1 && p->b_count >= B_L1) ||
            (p->level == 2 && p->b_count >= B_L2) ||
            (p->level == 3 && p->b_count >= B_L3)) {
            p->level = (p->level < 4) ? p->level + 1 : 4;
            p->b_count = 0;
        }
    } else {
        p->g_count++;
        if ((p->level == 2 && p->g_count >= G_L2) ||
            (p->level == 3 && p->g_count >= G_L3) ||
            (p->level == 4 && p->g_count >= G_L4)) {
            p->level = (p->level > 1) ? p->level - 1 : 1;
            p->g_count = 0;
        }
    }
}

void read_process_input() {
    char input[100];

    while (fgets(input, sizeof(input), stdin) != NULL && strncmp(input, "done", 4) != 0) {
        uint64_t time, run, io, repeat;
        int pid;
        if (sscanf(input, "%" SCNu64 " %d %" SCNu64 " %" SCNu64 " %" SCNu64, &time, &pid, &run, &io, &repeat) == 5) {
            Process p = {.pid = pid, .arrival_time = time, .remaining_burst = run, .remaining_io = io, .level = 1, .b_count = 0, .g_count = 0, .completed = false};
            init_queue(&p.behaviors, sizeof(ProcessBehavior), true, NULL, true);

            for (int i = 0; i < repeat; i++) {
                ProcessBehavior b = {.cpuburst = run, .ioburst = io};
                add_to_queue(&p.behaviors, &b, 1);
            }

            ProcessBehavior last_b = {.cpuburst = run, .ioburst = 0};
            add_to_queue(&p.behaviors, &last_b, 1);
            add_to_queue(&ArrivalQ, &p, INT32_MAX - p.arrival_time);

            printf("CREATE: Process %d entered the ready queue at time %" PRIu64 ".\n", pid, time);
        } else {
            printf("Invalid input format. Please try again.\n");
        }
    }
}

int main() {
    int clock = 0;
    int cpu_usage = 0;

    initialize_queues();
    read_process_input();
    while (queue_length(&ArrivalQ) > 0 || queue_length(&L1) > 0 || queue_length(&L2) > 0 || queue_length(&L3) > 0 || queue_length(&L4) > 0) {
        Process *p = NULL;

        // Check the ArrivalQ for processes that should be enqueued
        if (!empty_queue(&ArrivalQ)) {
            p = (Process *)remove_from_front(&ArrivalQ, &null_process);
            if (p->arrival_time <= clock && !p->completed) {    
                enqueue_process(p);
            } else {
                // If the process is not ready to be enqueued, put it back
		add_to_queue(&ArrivalQ, p, INT32_MAX - p->arrival_time);
                p = NULL; // Reset p to avoid processing it further
            }
        }

        // Select the next process to execute
        if (!empty_queue(&L1)) {
            p = (Process *)remove_from_front(&L1, &null_process);
        } else if (!empty_queue(&L2)) {
            p = (Process *)remove_from_front(&L2, &null_process);
        } else if (!empty_queue(&L3)) {
            p = (Process *)remove_from_front(&L3, &null_process);
        } else if (!empty_queue(&L4)) {
            p = (Process *)remove_from_front(&L4, &null_process);
        }

        // Execute the selected process
        if (p && !p->completed) {
            execute_process(p, &cpu_usage, &clock);
        } else {
            clock++;
            cpu_usage++;
        }
    }
// I wanted to do something where the code loops over each process to get the exact time unfortunately I didn't have enuogh time to complete/
    printf("Scheduler shutdown at time %d.\n", clock);
    printf("Total CPU usage for all processes scheduled:\n");
    printf("Process <<null>>: %d time units.\n", cpu_usage);
    return 0;
}
