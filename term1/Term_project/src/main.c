//
// Project: CPU scheduling simulator
// Author: JangHo LIM
// Affiliation: Korea University
// Date: 2024.05.30
//

#include "../include/header.h"
#include "../include/constant.h"
#include "../include/process.h"
#include "../include/queue.h"
#include "../include/priority_queue.h"
#include "../include/result.h"
#include "../include/algorithm.h"

int main()
{
    //process test
//  Process** p = init_process(PROCESS_COUNT);
    Process* p[PROCESS_COUNT];

    for(int i = 0; i < PROCESS_COUNT; i++)
    {
        p[i] = malloc(sizeof(Process));
    }

    create_process(p, PROCESS_COUNT);
    print_process(p, PROCESS_COUNT);

    result *SJF_result, *FCFS_result, *PRIORITY_result, *RR_result;
    RR_result = init_result("Round-Robin schedule");
    Process* p_copy[PROCESS_COUNT];
    for(int i = 0; i < PROCESS_COUNT; i++) p_copy[i] = copy_process(p[i]);

    print_process(p_copy, PROCESS_COUNT);
    FCFS(p_copy, FCFS_result);



    //Process* p_copy2[PROCESS_COUNT];
    //for(int i = 0; i < PROCESS_COUNT; i++) p_copy2[i] = copy_process(p[i]);

    //print_process(p_copy2, PROCESS_COUNT);
    //SJF(p_copy2, SJF_result ,true);

    //Process* p_copy3[PROCESS_COUNT];
    //for(int i = 0; i < PROCESS_COUNT; i++) p_copy3[i] = copy_process(p[i]);
    
    //print_process(p, PROCESS_COUNT);
    Round_Robin(p, RR_result, 2);
    //print_gantt_chart(RR_result);
    print_gantt_chart(RR_result);




    return 0;
}




