#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "../include/header.h"
#include "../include/constant.h"
#include "../include/queue.h"
#include "../include/process.h"
#include "../include/priority_queue.h"
#include "../include/result.h"

//void FCFS(Process* p[], result *res);
void FCFS(Process* p[], result* FCFS_result);
void SJF(Process *p[], result* SJF_result ,bool preemptive);
void PRIORITY_schedule(Process *p[], result* PRIORITY_result ,bool preemptive);
void Round_Robin(Process *p[], result* RR_result, int time_quantum);
void set_new_queue(Process* p[], PriorityQueue* new_queue);

#endif