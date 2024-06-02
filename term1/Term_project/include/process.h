//
// Project: CPU scheduling simulator
// Author: JangHo LIM
// Affiliation: Korea University
// Date: 2024.05.30
//

#ifndef PROCESS_H
#define PROCESS_H

#include "header.h"
#include "constant.h"

typedef struct {
    int pid;
    int arrived_time;
    int cpu_burst_time;
    int io_burst_time;
    int priority;
    int remaining_time;
    int waiting_time;
    int complete_time;
    int response_time;
    int start_time;
    int turnaround_time;
    char state[10];
    char type[20];
    int io_interval;
    int io_remain_time;
    int resume_time;

} Process;

void create_process(Process* p[], int N);
void print_process(Process* p[], int size);
Process* copy_process(const Process* original);

#endif


