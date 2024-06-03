#include "../include/algorithm.h"
#define high_queue_allocation 6
#define middle_queue_allocation 15

void Multilevel_feedback_queue(Process *p[], result* MLFQ_result)
{
    Queue* ready_queue_high      = init_Queue();      //FCFS
    Queue* ready_queue_middle    = init_Queue();      //FCFS
    Queue* ready_queue_low       = init_Queue();      //FCFS

    PriorityQueue* new_queue       = init_PriorityQueue(true);
    PriorityQueue* waiting_queue    = init_PriorityQueue(true);

    Queue* done_queue   = init_Queue();
    Queue* run          = init_Queue();
    set_new_queue(p, new_queue);

    for(int i = 0; i < PROCESS_COUNT; i++)      //우선순위 초기화
    {
        p[i]->priority = 1;
    }

    int time = 0;

    while(size_queue(done_queue) < PROCESS_COUNT)
    {
        //
        // ready queue section
        //
        // new process
        while (!isEmpty_PQ(new_queue) && time >= front_pq(new_queue)->arrived_time)
        {
            strcpy(front_pq(new_queue)->state, "ready");
            push_queue(ready_queue_high, pop_pq(new_queue));
        }
        // waiting process
        while (!isEmpty_PQ(waiting_queue) && front_pq(waiting_queue)->io_remain_time <= 0)
        {
            strcpy(front_pq(waiting_queue)->state, "ready");

            if(strcmp(front_pq(waiting_queue)->type, "IO_bounded") == 0)    
                front_pq(waiting_queue)->io_remain_time = front_pq(waiting_queue)->io_burst_time;


            if(front_pq(waiting_queue)->priority == 1)
            {
                push_queue(ready_queue_high, pop_pq(waiting_queue));
            }
            else if(front_pq(waiting_queue)->priority == 2)
            {
                push_queue(ready_queue_middle, pop_pq(waiting_queue));
            }
            else
            {
                push_queue(ready_queue_low, pop_pq(waiting_queue));
            }
        }


        //
        // preemptrive section
        //
        // 1. complete
        if (!isEmpty_queue(run) && run->data[0]->remaining_time == 0)
        {
            strcpy(run->data[0]->state, "done");
            run->data[0]->complete_time = time;
            run->data[0]->turnaround_time = run->data[0]->complete_time - run->data[0]->arrived_time;
            run->data[0]->response_time = run->data[0]->start_time - run->data[0]->arrived_time;

            executed_node node1 = {run->data[0]->pid, run->data[0]->resume_time, run->data[0]->complete_time, "Done"};
            record_result(MLFQ_result, &node1);
            push_queue(done_queue, pop_queue(run));
        }
        // 2.IO_burst
        //cpu_bounded-> 1 interrupt
        if(!isEmpty_queue(run) && 
            strcmp(run->data[0]->type, "CPU_bounded") == 0 && 
            run->data[0]->io_interval == run->data[0]->cpu_consume_time &&
            run->data[0]->io_remain_time != 0)
            {
                //printf("cpu bounded : preempted!\n");
                strcpy(run->data[0]->state, "waiting");
                
                executed_node node_wait = {run->data[0]->pid, run->data[0]->resume_time, time, "IO_waiting"};
                record_result(MLFQ_result, &node_wait);
                push_pq(waiting_queue, pop_queue(run), run->data[0]->io_remain_time);
            }

        //IO_bounded-> steady interrupt
        if(!isEmpty_queue(run) &&
           strcmp(run->data[0]->type, "IO_bounded") == 0 &&
           run->data[0]->cpu_consume_time % run->data[0]->io_interval == 0)        //io_remain_time = process restart or start time
        {
                //printf("IO_bounded : preempted!\n");
                strcpy(run->data[0]->state, "waiting");
                executed_node node_wait = {run->data[0]->pid, run->data[0]->resume_time, time, "IO_waiting"};
                record_result(MLFQ_result, &node_wait);

                //run->data[0]->io_remain_time = run->data[0]->io_interval;
                push_pq(waiting_queue, pop_queue(run), run->data[0]->io_remain_time);

        }
        // 3. Multilevel_feedback_alg
        if(!isEmpty_queue(run) && !isEmpty_queue(ready_queue_high))
        {
            if(run->data[0]->priority == 2){
                strcpy(run->data[0]->state, "ready");
                executed_node node_wait = {run->data[0]->pid, run->data[0]->resume_time, time, "Preemptive"};
                record_result(MLFQ_result, &node_wait);

                push_queue(ready_queue_middle, pop_queue(run));
            }
            if(run->data[0]->priority == 3){
                strcpy(run->data[0]->state, "ready");
                executed_node node_wait = {run->data[0]->pid, run->data[0]->resume_time, time, "Preemptive"};
                record_result(MLFQ_result, &node_wait);

                push_queue(ready_queue_low, pop_queue(run));
            }
        }

        if(!isEmpty_queue(run) && !isEmpty_queue(ready_queue_middle))
        {
            if(run->data[0]->priority == 3){
                strcpy(run->data[0]->state, "ready");
                executed_node node_wait = {run->data[0]->pid, run->data[0]->resume_time, time, "Preemptive"};
                record_result(MLFQ_result, &node_wait);

                push_queue(ready_queue_low, pop_queue(run));
            }
        }

        if(!isEmpty_queue(run))
        {
            if(run->data[0]->priority == 1 && time - run->data[0]->resume_time >= high_queue_allocation){
                strcpy(run->data[0]->state, "ready");
                executed_node node_wait = {run->data[0]->pid, run->data[0]->resume_time, time, "Preemptive"};
                record_result(MLFQ_result, &node_wait);
                run->data[0]->priority = 2;
                push_queue(ready_queue_middle, pop_queue(run));
            }

            else if(run->data[0]->priority == 2 && time - run->data[0]->resume_time >= middle_queue_allocation){
                strcpy(run->data[0]->state, "ready");
                executed_node node_wait = {run->data[0]->pid, run->data[0]->resume_time, time, "Preemptive"};
                record_result(MLFQ_result, &node_wait);
                run->data[0]->priority = 3;
                push_queue(ready_queue_low, pop_queue(run));
            }
        }
        //
        // Run section
        //

        if(isEmpty_queue(run))
        {
            if(!isEmpty_queue(ready_queue_high)){
                push_queue(run, pop_queue(ready_queue_high));
                strcpy(run->data[0]->state, "run");
                run->data[0]->resume_time = time;
                if(run->data[0]->start_time == 0)   run->data[0]->start_time = time;
            }
            else if(!isEmpty_queue(ready_queue_middle)){
                push_queue(run, pop_queue(ready_queue_middle));
                strcpy(run->data[0]->state, "run");
                run->data[0]->resume_time = time;
                if(run->data[0]->start_time == 0)   run->data[0]->start_time = time;
            }
            else if(!isEmpty_queue(ready_queue_low)){
                push_queue(run, pop_queue(ready_queue_low));
                strcpy(run->data[0]->state, "run");
                run->data[0]->resume_time = time;
                if(run->data[0]->start_time == 0)   run->data[0]->start_time = time;
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

        for (int i = ready_queue_high->front; i != ready_queue_high->rear + 1 && !isEmpty_queue(ready_queue_high); i = (i + 1) % QUEUE_SIZE)
        {
            ready_queue_high->data[i]->waiting_time++;
        }
        
        for (int i = ready_queue_middle->front; i != ready_queue_middle->rear + 1 && !isEmpty_queue(ready_queue_middle); i = (i + 1) % QUEUE_SIZE)
        {
            ready_queue_middle->data[i]->waiting_time++;
        }
        
        for (int i = ready_queue_low->front; i != ready_queue_low->rear + 1 && !isEmpty_queue(ready_queue_low); i = (i + 1) % QUEUE_SIZE)
        {
            ready_queue_low->data[i]->waiting_time++;
        }
    }
    evaluation(p, MLFQ_result);
}

