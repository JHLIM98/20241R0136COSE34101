//
// Project: CPU scheduling simulator
// Author: JangHo LIM
// Affiliation: Korea University
// Date: 2024.05.30
//

#include "../include/process.h"
void create_process(Process* p[], int N)
{
    srand(time(NULL));
    bool used_pid[PID_MAX+1] = {0};
    for(int i = 0; i < N; i++)
    {
        int random_pid;
        do{
            random_pid = rand() % PID_MAX + 1;
        }while(used_pid[random_pid]);
        
        p[i]->pid = random_pid;
        used_pid[random_pid] = 1;

        p[i]->arrived_time = rand() % ARRIVED_TIME_MAX;
        p[i]->cpu_burst_time = rand() % CPU_BURST_TIME_MAX + 5;
        p[i]->io_burst_time = rand() % IO_BURST_TIME_MAX + 1;
        p[i]->priority = rand() % PRIORITY_MAX + 1;
        p[i]->remaining_time = p[i]->cpu_burst_time;
        p[i]->waiting_time = 0;
        p[i]->complete_time = 0;
        p[i]->response_time = 0;
        p[i]->start_time = 0;
        p[i]->turnaround_time = 0;
        p[i]->resume_time = -1;         //시작하지 않음을 나타냄
        strcpy(p[i]->state,  "NEW");

        //cpu_bounded or io_bounded
        int probability = rand() % 8;
        if(probability != 0)
        {
            strcpy(p[i]->type, "CPU_bounded");
            p[i]->io_interval = rand()%p[i]->cpu_burst_time+1; 
        }
        else
        {
            strcpy(p[i]->type, "IO_bounded");
            p[i]->io_interval = rand()%IO_INTERVAL_MAX+1;
        }

        p[i]->io_remain_time = p[i]->io_burst_time;
    }
}

void print_process(Process* p[], int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("Process %d  --------------\n", i + 1);
        printf("  PID:\t\t\t%d\n", p[i]->pid);
        printf("  Arrived Time:\t\t%d\n", p[i]->arrived_time);
        printf("  CPU Burst Time:\t%d\n", p[i]->cpu_burst_time);
        printf("  I/O Burst Time:\t%d\n", p[i]->io_burst_time);
        printf("  Priority:\t\t%d\n", p[i]->priority);
        printf("  Remaining time:\t%d\n", p[i]->remaining_time);
        printf("  Waiting time:\t\t%d\n", p[i]->waiting_time);
        printf("  Complete time:\t%d\n", p[i]->complete_time);
        printf("  Response time:\t%d\n", p[i]->response_time);
        printf("  Turnaround time:\t%d\n", p[i]->turnaround_time);
        printf("  Start time:\t\t%d\n", p[i]->start_time);
        printf("  State:\t\t%s\n", p[i]->state);
        printf("  Type:\t\t\t%s\n", p[i]->type);
        printf("  IO_interval:\t\t%d\n", p[i]->io_interval);
        printf("  resume_time:\t\t%d\n", p[i]->resume_time);
        printf("  IO_remain_time:\t%d\n", p[i]->io_remain_time);
        printf("\n");
    }
}


Process* copy_process(const Process* original) {
    if (original == NULL) {
        return NULL;
    }

    Process* copy = (Process*)malloc(sizeof(Process));
    if (copy == NULL) {
        perror("Failed to allocate memory for process copy");
        exit(EXIT_FAILURE);
    }

    copy->pid = original->pid;
    copy->arrived_time = original->arrived_time;
    copy->cpu_burst_time = original->cpu_burst_time;
    copy->io_burst_time = original->io_burst_time;
    copy->priority = original->priority;
    copy->remaining_time = original->remaining_time;
    copy->waiting_time = original->waiting_time;
    copy->complete_time = original->complete_time;
    copy->response_time = original->response_time;
    copy->start_time = original->start_time;
    copy->turnaround_time = original->turnaround_time;
    strcpy(copy->state, original->state);
    strcpy(copy->type, original->type);
    copy->io_interval = original->io_interval;
    copy->io_remain_time = original->io_remain_time;
    copy->resume_time = original->resume_time;

    return copy;
}