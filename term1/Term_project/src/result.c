//
// Project: CPU scheduling simulator
// Author: JangHo LIM
// Affiliation: Korea University
// Date: 2024.05.31
//

#include "../include/result.h"
#include "../include/process.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

result* init_result(char *name)
{
    result *res = (result*)malloc(sizeof(result));
    strcpy(res->schedule_name, name);
    res->node_count = 0;
    res->result_capacity = 10;
    res->exe_node = (executed_node*)malloc(sizeof(executed_node) * res->result_capacity);
    return res;
}

void record_result(result* res, executed_node* node)
{
    if(res->node_count >= res->result_capacity) {
        res->result_capacity *= 2;
        res->exe_node = (executed_node*)realloc(res->exe_node, sizeof(executed_node) * res->result_capacity);
    }
    res->exe_node[res->node_count++] = *node;
}

void delete_result(result *res)
{
    free(res->exe_node);
    free(res);
}

void print_result(result *res)
{
    printf("\n*****Print Result*****\n");
    printf("schedule name : %s\n", res->schedule_name);
    for(int i = 0; i < res->node_count; i++) {
        printf("PID: %-5d\t Start: %-5d\t End: %-5d\t Reason: %-8s\n", 
               res->exe_node[i].pid, res->exe_node[i].start_time, res->exe_node[i].end_time, res->exe_node[i].reason);
    }
    printf("sumary_info\n\n");
    printf("Total Turnaround Time  : %d\n", res->total_turnaround_time);
    printf("Total Waiting Time     : %d\n", res->total_wating_time);
    printf("Average Turnaround Time: %.2f\n", res->avg_turnaround_time);
    printf("Average Waiting Time   : %.2f\n", res->avg_wating_time);
    printf("Average Response Time  : %.2f\n", res->avg_response_time);

    printf("*****Print End*****\n\n");
}



void evaluation(Process* p[], result *res)
{
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int process_count = PROCESS_COUNT;

    for (int i = 0; i < process_count; i++) {
        if (p[i] == NULL) {
                printf("p[%d] is NULL\n", i);
                break;
        }
        total_turnaround_time += p[i]->turnaround_time;
        total_waiting_time += p[i]->waiting_time;
        total_response_time += p[i]->response_time;
    }

    
    res->total_turnaround_time = total_turnaround_time;
    res->total_wating_time = total_waiting_time;
    res->avg_turnaround_time = (float)total_turnaround_time / process_count;
    res->avg_wating_time = (float)total_waiting_time / process_count;
    res->avg_response_time = (float)total_response_time / process_count;
    
}


