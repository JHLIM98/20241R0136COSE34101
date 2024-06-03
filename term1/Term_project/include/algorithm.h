#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "../include/header.h"
#include "../include/constant.h"
#include "../include/queue.h"
#include "../include/process.h"
#include "../include/priority_queue.h"
#include "../include/result.h"


void FCFS(Process* p[], result* FCFS_result);
void SJF(Process *p[], result* SJF_result ,bool preemptive);
void PRIORITY_schedule(Process *p[], result* PRIORITY_result ,bool preemptive);
void Round_Robin(Process *p[], result* RR_result, int time_quantum);
void Multilevel_queue(Process *p[], result* MLQ_result, int time_quantum);
void Multilevel_feedback_queue(Process *p[], result* MLQ_result);
void set_new_queue(Process* p[], PriorityQueue* new_queue);
void Weighted_Round_Robin(Process *p[], result* WRR_result, int time_quantum);
void DPP_schedule(Process *p[], result* DPP_result);
void rate_monotonic_schedule(Process* p[], result* RMS_result);


#endif