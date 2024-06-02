#include "../include/algorithm.h"


//void FCFS(Process* p[], result *res)
void FCFS(Process* p[], result* FCFS_result)
{
    Queue* ready_queue;
    PriorityQueue* waiting_queue;
    Queue* run;
    Queue* done_queue;
    PriorityQueue* new_queue;

    ready_queue = init_Queue();
    waiting_queue = init_PriorityQueue(true);
    done_queue = init_Queue();
    run = init_Queue();
    new_queue = init_PriorityQueue(true);
    
    set_new_queue(p, new_queue); 

    int time = 0;
    while (size_queue(done_queue) < PROCESS_COUNT)
    {   
        //
        // ready queue section
        //
        // new process
        while (!isEmpty_PQ(new_queue) && time >= front_pq(new_queue)->arrived_time)
        {
            strcpy(front_pq(new_queue)->state, "ready");
            push_queue(ready_queue, pop_pq(new_queue));
        }
        // waiting process
        while (!isEmpty_PQ(waiting_queue) && front_pq(waiting_queue)->io_remain_time <= 0)
        {
            strcpy(front_pq(waiting_queue)->state, "ready");
            if(strcmp(front_pq(waiting_queue)->type, "IO_bounded") == 0){
                front_pq(waiting_queue)->io_remain_time = front_pq(waiting_queue)->io_burst_time;
            }
            push_queue(ready_queue, pop_pq(waiting_queue));
        }
        
        //printf("ready is done\n");

        //
        // preemptive_section
        //
        // 1. complete
        if (!isEmpty_queue(run) && run->data[0]->remaining_time == 0)
        {
            strcpy(run->data[0]->state, "done");
            run->data[0]->complete_time = time;
            run->data[0]->turnaround_time = run->data[0]->complete_time - run->data[0]->arrived_time;
            run->data[0]->response_time = run->data[0]->start_time - run->data[0]->arrived_time;
            
            executed_node node1 = {run->data[0]->pid, run->data[0]->resume_time, run->data[0]->complete_time, "Done"};
            record_result(FCFS_result, &node1);
            
            push_queue(done_queue, pop_queue(run));
        }

        // 2. IO_burst
        //cpu_bounded-> 1 interrupt
        if(!isEmpty_queue(run) && 
            strcmp(run->data[0]->type, "CPU_bounded") == 0 && 
            run->data[0]->io_interval == run->data[0]->cpu_consume_time &&
            run->data[0]->io_remain_time != 0)
            {
                //printf("cpu bounded : preempted!\n");
                strcpy(run->data[0]->state, "waiting");
                
                executed_node node_wait = {run->data[0]->pid, run->data[0]->resume_time, time, "IO_waiting"};
                record_result(FCFS_result, &node_wait);
                push_pq(waiting_queue, pop_queue(run), run->data[0]->io_remain_time);
            }

        //IO_bounded-> steady interrupt
        if(!isEmpty_queue(run) &&
        strcmp(run->data[0]->type, "IO_bounded") == 0 &&
        run->data[0]->cpu_consume_time % run->data[0]->io_interval == 0)        
        {
                //printf("IO_bounded : preempted!\n");
                strcpy(run->data[0]->state, "waiting");
                
                executed_node node_wait = {run->data[0]->pid, run->data[0]->resume_time, time, "IO_waiting"};
                record_result(FCFS_result, &node_wait);
                push_pq(waiting_queue, pop_queue(run), run->data[0]->io_remain_time);

        }


        //
        // run section
        //

        // run new task
        if (isEmpty_queue(run) && !isEmpty_queue(ready_queue))
        {
            push_queue(run, pop_queue(ready_queue));
            strcpy(run->data[0]->state, "run");
            
            run->data[0]->resume_time = time;           // run 재개 시간

            if (run->data[0]->start_time == 0) {        // 최초 시작 시간
                run->data[0]->start_time = time;
            }
        }



        //
        // increase time section
        //
        time++;
        if (!isEmpty_queue(run)){
            run->data[0]->remaining_time--;
            run->data[0]->cpu_consume_time++;
        }

        for (int i = 0; i <= waiting_queue->rear && !isEmpty_PQ(waiting_queue); i++)
        {
            waiting_queue->data[i]->io_remain_time--;
        }

        for (int i = ready_queue->front; i != ready_queue->rear + 1 && !isEmpty_queue(ready_queue); i = (i + 1) % QUEUE_SIZE)
        {
            ready_queue->data[i]->waiting_time++;
        }


    }
    evaluation(p, FCFS_result);
    //print_result(FCFS_result);
    //printf("\n\n*****FCFS is Done*****\n\n");
}