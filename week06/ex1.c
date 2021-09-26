#include <stdio.h>
#include <stdlib.h>

#define CPU_COUNT 1

struct process {
    int completion_t;  // Completion unit time
    int turn_around_t; // Turn Around unit time
    int waiting_t;     // Waiting unit time
    int burst_t;       // Burst unit time
    int cpu_t;         // Spent CPU unit time
    int arrival_t;     // Arrival unit time
    int stop_t;        // Unit time when process stopped
};

struct {
    struct process** ready;    // Buffer of ready-to-run processes
    int ready_cnt;
    struct process** finished; // Buffer of finished processes
    int finished_cnt;
    struct process** future;   // Buffer of not yet arrived processes
    int future_cnt;
    struct process** running;  // Buffer of currently running processes
    int running_cnt;

    void (*strategy)(int);    // strategy scheduler uses
    double atat;               // Average turn around time
    double awt;                // Average waiting time
    int active;                // Flag whether scheduler is active

    int tick_cnt;              // Unit time clock
} scheduler;

int proc_num;  // Number of processes initially

void proc_list_init();  // Initialize list of processes from stdin
void scheduler_init();  // Initialize and allocate memory for scheduler
void scheduler_tick();  // Perform one iteration of scheduler
void scheduler_run(struct process* proc, int cpu); // Schedule specific process to run
void fcfs_strat(int cpu); // First come first served strategy
void sj_strat(int cpu);   // Shortest job first strategy
void rr_strat(int cpu);   // Round robin strategy
void proc_tick(int cpu); // Perform one iteration of process
void proc_report(struct process* proc); // Write process info report to stdout
void general_report();   // Write general scheduler report to stdout
void remove_proc(void** arr, int *n, int index); // Remove from processes list

struct process* proc_list; // Initial list of processes

void remove_proc(void** arr, int *n, int index) {
    if (index < 0 || index >= *n) {
        return;
    }
    struct process** pl = (struct process**)arr;
    for (int i = 0; i + 1 < *n; ++i) {
        if (i >= index) {
            arr[i] = arr[i + 1];
        }
    }
    (*n)--;
}

void proc_list_init() {
    printf("Please, enter the number of processes.\n");
    scanf("%d", &proc_num);
    printf("Please, enter arrival time and burst time for each process.\n");
    proc_list = (struct process*)malloc(proc_num * sizeof(struct process));
    for (int i = 0; i < proc_num; ++i) {
        scanf("%d%d", &proc_list[i].arrival_t, &proc_list[i].burst_t);
        proc_list[i].completion_t = 0;
        proc_list[i].stop_t = proc_list[i].arrival_t;
        proc_list[i].cpu_t = 0;
        proc_list[i].turn_around_t = 0;
        proc_list[i].waiting_t = 0;
    }
}

void scheduler_init() {
    scheduler.strategy = fcfs_strat;
    scheduler.atat = 0;
    scheduler.awt = 0;
    scheduler.active = 1;

    scheduler.tick_cnt = 0;

    scheduler.running = (struct process**)malloc(CPU_COUNT * sizeof(struct process*));
    scheduler.running_cnt = 0;
    scheduler.ready = (struct process**)malloc(proc_num * sizeof(struct process*));
    scheduler.ready_cnt = 0;
    scheduler.finished = (struct process**)malloc(proc_num * sizeof(struct process*));
    scheduler.finished_cnt = 0;
    scheduler.future = (struct process**)malloc(proc_num * sizeof(struct process*));
    scheduler.future_cnt = 0;

    for (int i = 0; i < proc_num; ++i) {
        scheduler.future[scheduler.future_cnt++] = &proc_list[i];
    }
}

void scheduler_tick(void (*sched_strat)(int)) {
    for (int i = 0; i < scheduler.future_cnt; ++i) {
        if (scheduler.future[i]->arrival_t <= scheduler.tick_cnt) {
            struct process* proc = scheduler.future[i];
            remove_proc((void**)scheduler.future, &scheduler.future_cnt, i--);
            scheduler.ready[scheduler.ready_cnt++] = proc;
        }
    }
    scheduler.strategy(0);
    if (!(scheduler.future_cnt || scheduler.ready_cnt || scheduler.running[0])) {
        scheduler.active = 0;
    }
}

void scheduler_run(struct process* proc, int cpu) {
    if (proc == NULL) {
        return;
    }
    if (scheduler.running[cpu] == proc) {
        return;
    }
    struct process* prev_proc = scheduler.running[cpu];
    scheduler.running[cpu] = proc;
    proc->waiting_t += scheduler.tick_cnt - proc->stop_t;
    if (prev_proc) {
        prev_proc->stop_t = scheduler.tick_cnt;
        scheduler.ready[scheduler.ready_cnt++] = prev_proc;
    }
}

void proc_tick(int cpu) {
    static int it = 0;
    struct process* proc = scheduler.running[cpu];
    if (proc == NULL) {
        return;
    }
    proc->cpu_t++;
    if (proc->cpu_t == proc->burst_t) {
        proc->completion_t = scheduler.tick_cnt + 1;
        proc->turn_around_t = proc->waiting_t + proc->burst_t;
        scheduler.finished[scheduler.finished_cnt++] = proc;
        scheduler.running[cpu] = NULL;
        proc_report(proc);
    }
}

/*
 * First Come First Served strategy
 * Simpliest strategy, which finds and schedules the process
 * with the earliest arrival time. As a result, it lowers
 * the throughput, increases average turn around time and
 * worsens the average waiting time
 * */
void fcfs_strat(int cpu) {
    struct process* proc = scheduler.running[cpu];
    if (proc != NULL) {
        return;
    }
    int index = -1;
    for (int i = 0; i < scheduler.ready_cnt; ++i) {
        if (!proc || proc->arrival_t > scheduler.ready[i]->arrival_t) {
            index = i;
            proc = scheduler.ready[i];
        }
    }
    remove_proc((void**)scheduler.ready, &scheduler.ready_cnt, index);
    scheduler_run(proc, cpu);
}

/*
 * Shortest Job first strategy
 * A bit trickier strategy. Executing the shortest processes
 * increases program throughput dramatically and lowers average 
 * turn around time, while completion of important, but long task
 * may take infinity if the source of infinitely many small 
 * jobs is provided
 * */
void sj_strat(int cpu) {
    struct process* proc = scheduler.running[cpu];
    int index = -1;
    for (int i = 0; i < scheduler.ready_cnt; ++i) {
        int new_t = scheduler.ready[i]->burst_t - scheduler.ready[i]->cpu_t;
        if (!proc || proc->burst_t - proc->cpu_t > new_t) {
            proc = scheduler.ready[i];
            index = i;
            printf("index: %d\n", index);
        }
    }
    remove_proc((void**)scheduler.ready, &scheduler.ready_cnt, index);
    scheduler_run(proc, cpu);
}

/*
 * Round Robin strategy
 * With some fixed quantum it becomes much easier to
 * fairly distribute the resources among all processes.
 * However, the problem arises when we try to choose the
 * quantum value. Very high values will equate this 
 * strategy to simple sequential execution, disabling
 * it's advantage.
 * */
void rr_strat(int cpu) {
    static int quantum = -1;
    static int cur_q = 0;
    if (quantum == -1) {
        printf("Please, specify the quantum:\n");
        scanf("%d", &quantum);
    }
    
    struct process* proc = scheduler.running[cpu];
    if (!proc || cur_q == quantum) {
        cur_q = 1;
        if (scheduler.ready_cnt == 0) {
            return;
        }
        proc = scheduler.ready[0];
        remove_proc((void**)scheduler.ready, &scheduler.ready_cnt, 0);
        scheduler_run(proc, 0);
    } else {
        cur_q++;
    }
}

void proc_report(struct process* proc) {
    printf("-----------------\n");
    printf("Process finished.\n");
    printf("Arrival time: %d\n", proc->arrival_t);
    printf("Completion time: %d\n", proc->completion_t);
    printf("Waiting time: %d\n", proc->waiting_t);
    printf("Turn around time: %d\n", proc->turn_around_t);
}

void general_report() {
    for (int i = 0; i < proc_num; ++i) {
        scheduler.awt += proc_list[i].waiting_t;
        scheduler.atat += proc_list[i].turn_around_t;
    }
    scheduler.awt /= proc_num;
    scheduler.atat /= proc_num;
    printf("------------\n");
    printf("General report: \n");
    printf("Average turn around time: %lf\n", scheduler.atat);
    printf("Average waiting time: %lf\n", scheduler.awt);
}

int main() {
    proc_list_init();
    scheduler_init();

    while (scheduler.active) {
        scheduler_tick(scheduler.strategy);
        proc_tick(0);
        scheduler.tick_cnt++;
    }
    general_report();
}
