//
// Project: CPU scheduling simulator
// Author: JangHo LIM
// Affiliation: Korea University
// Date: 2024.05.30
//

#ifndef RESULT_H
#define RESULT_H

#include "header.h"
#include "constant.h"
#include "process.h"

typedef struct executed_node {
    int pid;
    int start_time;
    int end_time;
    char reason[20];

} executed_node;

typedef struct {
    char schedule_name[50];
    executed_node* exe_node;
    int node_count;
    int result_capacity; 
    
    int total_turnaround_time;
    int total_wating_time;
    float avg_turnaround_time;
    float avg_wating_time;
    float avg_response_time;
} result;

typedef struct{
    char name[20];
    float avg_turnaround_time;
    float avg_response_time;
    float avg_waiting_time;
} schedule_performance;

result* init_result(char *name);
void record_result(result* res, executed_node* node);
void delete_result(result *res);
void print_result(result *res);
void print_gantt_chart(result *res);
void evaluation(Process* p[], result *res);
void print_sorted(schedule_performance sp[], int n);
#endif
