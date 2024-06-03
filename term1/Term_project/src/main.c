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
    Process* p[PROCESS_COUNT_MAX];


    printf("몇 개의 프로세스를 생성하시겠습니까?(최대 100개) : ");
    scanf("%d", &PROCESS_COUNT);
    printf("%d개의 프로세스를 생성합니다.\n", PROCESS_COUNT);

    for(int i = 0; i < PROCESS_COUNT; i++)
    {
        p[i] = malloc(sizeof(Process));
    }
    create_process(p, PROCESS_COUNT);


    result *SJF_result, *FCFS_result, *PRIORITY_result, *RR_result, *SJF_P_result, 
            *PRIORITY_P_result, *MLQ_result, *MLFQ_result, *WRR_result, *DPP_result
            ,*RMS_result;
    
    
    
    SJF_result      = init_result("SJF");
    FCFS_result     = init_result("FCFS");
    PRIORITY_result = init_result("PRIORITY");
    RR_result       = init_result("Round-Robin");
    SJF_P_result    = init_result("SJF_Preemptive");
    PRIORITY_P_result = init_result("PRIORITY_Preemptive");
    MLQ_result      = init_result("Multi_level_queue");
    MLFQ_result     = init_result("MLFQ_queue");
    WRR_result      = init_result("Weighted_RR");
    DPP_result      = init_result("Dynamic_Priority_Preemptive");
    RMS_result      = init_result("RMS");
    
    Process* p_copy1[PROCESS_COUNT_MAX];
    Process* p_copy2[PROCESS_COUNT_MAX];
    Process* p_copy3[PROCESS_COUNT_MAX];
    Process* p_copy4[PROCESS_COUNT_MAX];
    Process* p_copy5[PROCESS_COUNT_MAX];
    Process* p_copy6[PROCESS_COUNT_MAX];
    Process* p_copy7[PROCESS_COUNT_MAX];
    Process* p_copy8[PROCESS_COUNT_MAX];
    Process* p_copy9[PROCESS_COUNT_MAX];
    Process* p_copy10[PROCESS_COUNT_MAX];
    Process* p_copy11[PROCESS_COUNT_MAX];
    
    for(int i = 0; i < PROCESS_COUNT; i++) p_copy1[i] = copy_process(p[i]);
    for(int i = 0; i < PROCESS_COUNT; i++) p_copy2[i] = copy_process(p[i]);
    for(int i = 0; i < PROCESS_COUNT; i++) p_copy3[i] = copy_process(p[i]);
    for(int i = 0; i < PROCESS_COUNT; i++) p_copy4[i] = copy_process(p[i]);
    for(int i = 0; i < PROCESS_COUNT; i++) p_copy5[i] = copy_process(p[i]);
    for(int i = 0; i < PROCESS_COUNT; i++) p_copy6[i] = copy_process(p[i]);
    for(int i = 0; i < PROCESS_COUNT; i++) p_copy7[i] = copy_process(p[i]);
    for(int i = 0; i < PROCESS_COUNT; i++) p_copy8[i] = copy_process(p[i]);
    for(int i = 0; i < PROCESS_COUNT; i++) p_copy9[i] = copy_process(p[i]);
    for(int i = 0; i < PROCESS_COUNT; i++) p_copy10[i] = copy_process(p[i]);
    for(int i = 0; i < PROCESS_COUNT; i++) p_copy11[i] = copy_process(p[i]);

    int time_quantum = 4;


    FCFS(p_copy1, FCFS_result);
    SJF(p_copy2, SJF_result, false);
    SJF(p_copy3, SJF_P_result, true);
    PRIORITY_schedule(p_copy4, PRIORITY_result, false);
    PRIORITY_schedule(p_copy5, PRIORITY_P_result, true);
    Round_Robin(p_copy6, RR_result, time_quantum);
    Multilevel_queue(p_copy7, MLQ_result, time_quantum);
    Multilevel_feedback_queue(p_copy8, MLFQ_result); 
    Weighted_Round_Robin(p_copy9, WRR_result, time_quantum = 1);
    DPP_schedule(p_copy10, DPP_result);
    rate_monotonic_schedule(p_copy11, RMS_result);

    schedule_performance sp[10];

    strcpy(sp[0].name, "FCFS");
    sp[0].avg_turnaround_time = FCFS_result->avg_turnaround_time;
    sp[0].avg_response_time = FCFS_result->avg_response_time;
    sp[0].avg_waiting_time = FCFS_result->avg_wating_time;

    strcpy(sp[1].name, "SJF");
    sp[1].avg_turnaround_time = SJF_result->avg_turnaround_time;
    sp[1].avg_response_time = SJF_result->avg_response_time;
    sp[1].avg_waiting_time = SJF_result->avg_wating_time;

    strcpy(sp[2].name, "SJF_P");
    sp[2].avg_turnaround_time = SJF_P_result->avg_turnaround_time;
    sp[2].avg_response_time = SJF_P_result->avg_response_time;
    sp[2].avg_waiting_time = SJF_P_result->avg_wating_time;

    strcpy(sp[3].name, "PRIORITY");
    sp[3].avg_turnaround_time = PRIORITY_result->avg_turnaround_time;
    sp[3].avg_response_time = PRIORITY_result->avg_response_time;
    sp[3].avg_waiting_time = PRIORITY_result->avg_wating_time;

    strcpy(sp[4].name, "PRIORITY_P");
    sp[4].avg_turnaround_time = PRIORITY_P_result->avg_turnaround_time;
    sp[4].avg_response_time = PRIORITY_P_result->avg_response_time;
    sp[4].avg_waiting_time = PRIORITY_P_result->avg_wating_time;

    strcpy(sp[5].name, "RR");
    sp[5].avg_turnaround_time = RR_result->avg_turnaround_time;
    sp[5].avg_response_time = RR_result->avg_response_time;
    sp[5].avg_waiting_time = RR_result->avg_wating_time;

    strcpy(sp[6].name, "MLQ");
    sp[6].avg_turnaround_time = MLQ_result->avg_turnaround_time;
    sp[6].avg_response_time = MLQ_result->avg_response_time;
    sp[6].avg_waiting_time = MLQ_result->avg_wating_time;

    strcpy(sp[7].name, "MLFQ");
    sp[7].avg_turnaround_time = MLFQ_result->avg_turnaround_time;
    sp[7].avg_response_time = MLFQ_result->avg_response_time;
    sp[7].avg_waiting_time = MLFQ_result->avg_wating_time;

    strcpy(sp[8].name, "WRR");
    sp[8].avg_turnaround_time = WRR_result->avg_turnaround_time;
    sp[8].avg_response_time = WRR_result->avg_response_time;
    sp[8].avg_waiting_time = WRR_result->avg_wating_time;

    strcpy(sp[9].name, "DPP");
    sp[9].avg_turnaround_time = DPP_result->avg_turnaround_time;
    sp[9].avg_response_time = DPP_result->avg_response_time;
    sp[9].avg_waiting_time = DPP_result->avg_wating_time;


    int choice;
    printf("\n\n");
    while (1) {
        printf("출력할 결과를 선택하세요:\n");
        printf("001: FCFS 결과 및 간트 차트 출력\n");
        printf("002: SJF 결과 및 간트 차트 출력\n");
        printf("003: SJF_Preemptive 결과 및 간트 차트 출력\n");
        printf("004: PRIORITY 결과 및 간트 차트 출력\n");
        printf("005: PRIORITY_Preemptive 결과 및 간트 차트 출력\n");
        printf("006: RR 결과 및 간트 차트 출력\n");
        printf("007: MLQ 결과 및 간트 차트 출력\n");
        printf("008: MLFQ 결과 및 간트 차트 출력\n");
        printf("009: WRR 결과 및 간트 차트 출력\n");
        printf("010: DPP 결과 및 간트 차트 출력\n");
        printf("011: RMS 결과 및 간트 차트 출력\n");
        printf("888: 전체 스케줄링 비교 \n");
        printf("999: 생성된 프로세스 정보 출력\n");
        printf("0: 종료\n");

        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                print_result(FCFS_result);
                print_gantt_chart(FCFS_result);
                break;
            case 2:
                print_result(SJF_result);
                print_gantt_chart(SJF_result);
                break;
            case 3:
                print_result(SJF_P_result);
                print_gantt_chart(SJF_P_result);
                break;
            case 4:
                print_result(PRIORITY_result);
                print_gantt_chart(PRIORITY_result);
                break;
            case 5:
                print_result(PRIORITY_P_result);
                print_gantt_chart(PRIORITY_P_result);
                break;
            case 6:
                print_result(RR_result);
                print_gantt_chart(RR_result);
                break;
            case 7:
                print_result(MLQ_result);
                print_gantt_chart(MLQ_result);
                break;
            case 8:
                print_result(MLFQ_result);
                print_gantt_chart(MLFQ_result);
                break;
            case 9:
                print_result(WRR_result);
                print_gantt_chart(WRR_result);
                break;
            case 10:
                print_result(DPP_result);
                print_gantt_chart(DPP_result);
                break;
            case 11:
                print_result(RMS_result);
                print_gantt_chart(RMS_result);
                break;
            case 888:
                printf("\n**********스케줄링 성능 비교**********\n\n");
                
                printf("***FCFS 스케줄링***\n\n");
                printf("평균 대기 시간:\t%-8.2f\n", FCFS_result->avg_wating_time);
                printf("평균 처리 시간:\t%-8.2f\n", FCFS_result->avg_turnaround_time);
                printf("평균 응답 시간:\t%-8.2f\n\n", FCFS_result->avg_response_time);
                
                printf("***SJF 스케줄링***\n\n");
                printf("평균 대기 시간:\t%-8.2f\n", SJF_result->avg_wating_time);
                printf("평균 처리 시간:\t%-8.2f\n", SJF_result->avg_turnaround_time);
                printf("평균 응답 시간:\t%-8.2f\n\n", SJF_result->avg_response_time);
                
                printf("***선점형 SJF 스케줄링***\n\n");
                printf("평균 대기 시간:\t%-8.2f\n", SJF_P_result->avg_wating_time);
                printf("평균 처리 시간:\t%-8.2f\n", SJF_P_result->avg_turnaround_time);
                printf("평균 응답 시간:\t%-8.2f\n\n", SJF_P_result->avg_response_time);
                
                printf("***우선순위 스케줄링***\n\n");
                printf("평균 대기 시간:\t%-8.2f\n", PRIORITY_result->avg_wating_time);
                printf("평균 처리 시간:\t%-8.2f\n", PRIORITY_result->avg_turnaround_time);
                printf("평균 응답 시간:\t%-8.2f\n\n", PRIORITY_result->avg_response_time);

                printf("***선점형 우선순위 스케줄링***\n\n");
                printf("평균 대기 시간:\t%-8.2f\n", PRIORITY_P_result->avg_wating_time);
                printf("평균 처리 시간:\t%-8.2f\n", PRIORITY_P_result->avg_turnaround_time);
                printf("평균 응답 시간:\t%-8.2f\n\n", PRIORITY_P_result->avg_response_time);

                printf("***라운드 로빈 스케줄링***\n\n");
                printf("평균 대기 시간:\t%-8.2f\n", RR_result->avg_wating_time);
                printf("평균 처리 시간:\t%-8.2f\n", RR_result->avg_turnaround_time);
                printf("평균 응답 시간:\t%-8.2f\n\n", RR_result->avg_response_time);

                printf("***다단계 큐 스케줄링***\n\n");
                printf("평균 대기 시간:\t%-8.2f\n", MLQ_result->avg_wating_time);
                printf("평균 처리 시간:\t%-8.2f\n", MLQ_result->avg_turnaround_time);
                printf("평균 응답 시간:\t%-8.2f\n\n", MLQ_result->avg_response_time);

                printf("***다단계 피드백 큐 스케줄링***\n\n");
                printf("평균 대기 시간:\t%-8.2f\n", MLFQ_result->avg_wating_time);
                printf("평균 처리 시간:\t%-8.2f\n", MLFQ_result->avg_turnaround_time);
                printf("평균 응답 시간:\t%-8.2f\n\n", MLFQ_result->avg_response_time);

                printf("***가중치 라운드 로빈 스케줄링***\n\n");
                printf("평균 대기 시간:\t%-8.2f\n", WRR_result->avg_wating_time);
                printf("평균 처리 시간:\t%-8.2f\n", WRR_result->avg_turnaround_time);
                printf("평균 응답 시간:\t%-8.2f\n\n", WRR_result->avg_response_time);
                
                printf("***선혐형 동적 우선순위 스케줄링***\n\n");
                printf("평균 대기 시간:\t%-8.2f\n", DPP_result->avg_wating_time);
                printf("평균 처리 시간:\t%-8.2f\n", DPP_result->avg_turnaround_time);
                printf("평균 응답 시간:\t%-8.2f\n\n", DPP_result->avg_response_time);

                print_sorted(sp, 10);

                printf("\n**********스케줄링 성능 비교 끝**********\n\n");
                break;

            case 999:
                print_process(p, PROCESS_COUNT);
                break;
            case 0:
                // 메모리 해제
                free(FCFS_result);
                free(SJF_result);
                free(SJF_P_result);
                free(PRIORITY_result);
                free(PRIORITY_P_result);
                free(RR_result);
                free(MLQ_result);
                free(MLFQ_result);
                free(WRR_result);
                free(DPP_result);
                free(RMS_result);
                return 0;
            default:
                printf("잘못된 선택입니다. 다시 시도하세요.\n");
                break;
        }
    }


    return 0;
}

