#include "../include/algorithm.h"
#include "../include/result.h"


typedef struct {
    int pid;
    char *gantt;
} pid_gantt;


void print_gantt_chart(result *res) 
{

    printf("\n*****Gantt Chart*****\n");
    printf("schedule name : %s\n", res->schedule_name);

    // chart 1
    int group_size = 10;
    int num_groups = (res->node_count + group_size - 1) / group_size; // 그룹의 수 계산
    printf("\n");
    for (int group = 0; group < num_groups; group++) {
        int start = group * group_size;
        int end = (group + 1) * group_size;
        
        if (end > res->node_count) {        //마지막 그룹 처리.
            end = res->node_count;
        }


        for (int i = start; i < end; i++) {
            printf("  ----------  ");
        }
        printf("\n");

        for (int i = start; i < end; i++) {
            printf(" | PID : %-2d | ", res->exe_node[i].pid);
        }
        printf("\n");

        for (int i = start; i < end; i++) {
            printf("  ----------  ");
        }
        printf("\n");

        for (int i = start; i < end; i++) {
            printf("  %-3d     %-3d ", res->exe_node[i].start_time, res->exe_node[i].end_time);
        }
        printf("\n");
    }


    // chart 2
    printf("\n\n\n*********Chart 2*********\n\n\n");
    int max_time = res->exe_node[res->node_count-1].end_time;;
    pid_gantt *pid_gantts = malloc(res->node_count * sizeof(pid_gantt));
    int unique_pid_count = 0;

    for (int i = 0; i < res->node_count; i++) {
        executed_node node = res->exe_node[i];

        // 이미 존재하는 PID인지 확인
        bool found = false;
        for (int j = 0; j < unique_pid_count; j++) {
            if (pid_gantts[j].pid == node.pid) {
                found = true;
                break;
            }
        }

        // 존재하지 않으면 새로운 PID 추가
        if (!found) {
            pid_gantts[unique_pid_count].pid = node.pid;
            pid_gantts[unique_pid_count].gantt = malloc((max_time + 1) * sizeof(char));
            for (int k = 0; k < max_time; k++) {
                pid_gantts[unique_pid_count].gantt[k] = ' ';
            }
            pid_gantts[unique_pid_count].gantt[max_time] = '\0';
            unique_pid_count++;
        }

        // 해당 PID의 간트 차트 문자열에 실행 시간 추가
        for (int j = 0; j < unique_pid_count; j++) {
            if (pid_gantts[j].pid == node.pid) {
                for (int t = node.start_time; t < node.end_time; t++) {
                    pid_gantts[j].gantt[t] = '#';
                }
                break;
            }
        }
    }

    // 각 PID별로 간트 차트를 출력
    for (int i = 0; i < unique_pid_count; i++) {
        printf("PID: %-5d |%s| %d\n", pid_gantts[i].pid, pid_gantts[i].gantt, max_time);
        free(pid_gantts[i].gantt);
    }

    free(pid_gantts);   
    printf("\n*****Gantt Chart End*****\n\n");

}
    
