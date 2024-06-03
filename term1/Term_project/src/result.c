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


void print_sorted(schedule_performance sp[], int n) {
    schedule_performance sorted_sp[n];

    // average waiting time
    memcpy(sorted_sp, sp, n * sizeof(schedule_performance));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sorted_sp[i].avg_waiting_time > sorted_sp[j].avg_waiting_time) {
                schedule_performance temp = sorted_sp[i];
                sorted_sp[i] = sorted_sp[j];
                sorted_sp[j] = temp;
            }
        }
    }
    printf("\n***평균 대기 시간 순서***\n");
    for (int i = 0; i < n - 1; i++) {
        printf("%s < ", sorted_sp[i].name);
    }
    printf("%s\n", sorted_sp[n - 1].name);

    // turnaround time
    memcpy(sorted_sp, sp, n * sizeof(schedule_performance));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sorted_sp[i].avg_turnaround_time > sorted_sp[j].avg_turnaround_time) {
                schedule_performance temp = sorted_sp[i];
                sorted_sp[i] = sorted_sp[j];
                sorted_sp[j] = temp;
            }
        }
    }
    printf("\n***평균 처리 시간 순서***\n");
    for (int i = 0; i < n - 1; i++) {
        printf("%s < ", sorted_sp[i].name);
    }
    printf("%s\n", sorted_sp[n - 1].name);

    // average response time
    memcpy(sorted_sp, sp, n * sizeof(schedule_performance));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sorted_sp[i].avg_response_time > sorted_sp[j].avg_response_time) {
                schedule_performance temp = sorted_sp[i];
                sorted_sp[i] = sorted_sp[j];
                sorted_sp[j] = temp;
            }
        }
    }
    printf("\n***평균 응답 시간 순서***\n");
    for (int i = 0; i < n - 1; i++) {
        printf("%s < ", sorted_sp[i].name);
    }
    printf("%s\n", sorted_sp[n - 1].name);
}
