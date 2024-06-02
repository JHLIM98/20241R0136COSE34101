#include "../include/algorithm.h"

void SJF(Process *p[], result* SJF_result,bool preemptive)
{
    PriorityQueue* ready_queue = init_PriorityQueue(true);
    PriorityQueue* waiting_queue = init_PriorityQueue(true);
    PriorityQueue* new_queue;
    new_queue = init_PriorityQueue(true);
    Queue* done_queue = init_Queue();
    Queue* run = init_Queue();
    SJF_result = init_result("SJF RESULT");

    set_new_queue(p, new_queue);

    print_pq(new_queue);

    int time = 0;
    while(size_queue(done_queue) < PROCESS_COUNT)
    //while(time != 10 && size_queue(done_queue) < PROCESS_COUNT)
    {
        //
        // ready queue section
        //
        // new process
        while (!isEmpty_PQ(new_queue) && time >= front_pq(new_queue)->arrived_time)
        {
            strcpy(front_pq(new_queue)->state, "ready");
            int priority_SJF = front_pq(new_queue)->remaining_time;
            push_pq(ready_queue, pop_pq(new_queue), priority_SJF);
        }
        // waiting process
        while (!isEmpty_PQ(waiting_queue) && front_pq(waiting_queue)->io_remain_time <= 0)
        {
            strcpy(front_pq(waiting_queue)->state, "ready");
            
            if(strcmp(front_pq(waiting_queue)->type, "IO_bounded") == 0)    
                front_pq(waiting_queue)->io_remain_time = front_pq(waiting_queue)->io_burst_time;       // IO remaining time reset
            
            int priority_SJF = front_pq(waiting_queue)->remaining_time;
            push_pq(ready_queue, pop_pq(waiting_queue), priority_SJF);
        }


//        print_pq(ready_queue);

        
        //
        // preemptrive section
        //
        // 1.complete
        if (!isEmpty_queue(run) && run->data[0]->remaining_time == 0)
        {
            strcpy(run->data[0]->state, "done");
            run->data[0]->complete_time = time;
            run->data[0]->turnaround_time = run->data[0]->complete_time - run->data[0]->arrived_time;
            run->data[0]->response_time = run->data[0]->start_time - run->data[0]->arrived_time;

            executed_node node1 = {run->data[0]->pid, run->data[0]->resume_time, run->data[0]->complete_time, "Done"};
            record_result(SJF_result, &node1);
            push_queue(done_queue, pop_queue(run));
        }
        // 2.IO_burst
        //cpu_bounded-> 1 interrupt
        if(!isEmpty_queue(run) && 
            strcmp(run->data[0]->type, "CPU_bounded") == 0 && 
            run->data[0]->io_interval == time - run->data[0]->resume_time &&
            run->data[0]->io_remain_time != 0)
            {
                printf("cpu bounded : preempted!\n");
                strcpy(run->data[0]->state, "waiting");
                
                executed_node node_wait = {run->data[0]->pid, run->data[0]->resume_time, time, "IO_waiting"};
                record_result(SJF_result, &node_wait);
                push_pq(waiting_queue, pop_queue(run), run->data[0]->io_remain_time);
            }

        //IO_bounded-> steady interrupt
        if(!isEmpty_queue(run) &&
        strcmp(run->data[0]->type, "IO_bounded") == 0 &&
        run->data[0]->io_interval == time - run->data[0]->resume_time)        //io_remain_time = process restart or start time
        {
                printf("IO_bounded : preempted!\n");
                strcpy(run->data[0]->state, "waiting");
                executed_node node_wait = {run->data[0]->pid, run->data[0]->resume_time, time, "IO_waiting"};
                record_result(SJF_result, &node_wait);

                //run->data[0]->io_remain_time = run->data[0]->io_interval;
                push_pq(waiting_queue, pop_queue(run), run->data[0]->io_remain_time);

        }

        // 3.SJF_preemptive
        if(!isEmpty_queue(run) && !isEmpty_PQ(ready_queue) && preemptive == true)
        {
            if(run->data[0]->remaining_time > front_pq(ready_queue)->remaining_time)
            {
                printf("SJF : preemptive!!\n");
                strcpy(run->data[0]->state, "ready");
                executed_node node_wait = {run->data[0]->pid, run->data[0]->resume_time, time, "Preemptive"};
                record_result(SJF_result, &node_wait);

                push_pq(ready_queue, pop_queue(run), run->data[0]->remaining_time);
            }

        }


        //
        // run section
        //

        if(isEmpty_queue(run) && !isEmpty_PQ(ready_queue))
        {
            push_queue(run, pop_pq(ready_queue));
            strcpy(run->data[0]->state, "run");

            run->data[0]->resume_time = time;
            if(run->data[0]->start_time == 0)
                run->data[0]->start_time = time;
        }


        //
        // increase time section
        //
        time++;
        if(!isEmpty_queue(run))
            run->data[0]->remaining_time--;

        for(int i = 0; i <= waiting_queue->rear && !isEmpty_PQ(waiting_queue); i++)
        {
            waiting_queue->data[i]->io_remain_time--;
        }
        for(int i = 0; i <=ready_queue->rear && !isEmpty_PQ(ready_queue); i++)
        {
            ready_queue->data[i]->waiting_time++;
        }

    }
    print_result(SJF_result);

    printf("\n\n*****SJF is Done*****\n\n");
}