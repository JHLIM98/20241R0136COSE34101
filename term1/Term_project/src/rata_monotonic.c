#include "algorithm.h"

void rate_monotonic_schedule(Process* p[], result* RMS_result)
{
    PriorityQueue* ready_queue      = init_PriorityQueue(true);
    PriorityQueue* waiting_queue    = init_PriorityQueue(true);
    PriorityQueue* new_queue        = init_PriorityQueue(true);

    Queue* done_queue   = init_Queue();
    Queue* run          = init_Queue();

    // process to new Queue
    // set_new_queue(p, new_queue);
        for(int i = 0; i < PROCESS_COUNT; i++){
            p[i]->io_interval = p[i]->cpu_burst_time * PROCESS_COUNT * 2;
            p[i]->io_remain_time = p[i]->arrived_time + p[i]->io_interval;
            push_pq(new_queue, p[i], p[i]->arrived_time);

        }


    int time = 0;
    while(time < PROCESS_COUNT * CPU_BURST_TIME_MAX * 3)
    {   
        //
        // ready queue section
        //
        // new process
        
        while (!isEmpty_PQ(new_queue) && time >= front_pq(new_queue)->arrived_time)
        {
            strcpy(front_pq(new_queue)->state, "ready");
            int prior = front_pq(new_queue)->io_interval;
            push_pq(ready_queue, pop_pq(new_queue), prior);
        }
        // waiting process
        while (!isEmpty_PQ(waiting_queue) && front_pq(waiting_queue)->io_remain_time == 0)
        {
            strcpy(front_pq(waiting_queue)->state, "ready");
            front_pq(waiting_queue)->remaining_time = front_pq(waiting_queue)->cpu_burst_time;
            front_pq(waiting_queue)->io_remain_time = time + front_pq(waiting_queue)->io_interval;
            int prior = front_pq(waiting_queue)->io_interval;
            push_pq(ready_queue, pop_pq(waiting_queue), prior);
        }

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
            record_result(RMS_result, &node1);
            int priority1 = run->data[0]->io_interval;
            push_pq(waiting_queue, pop_queue(run), priority1);
        }

        //3. Priority_preemptive
        if(!isEmpty_queue(run) && !isEmpty_PQ(ready_queue))
        {
            if(run->data[0]->io_interval > front_pq(ready_queue)-> io_interval)
            {
                //printf("Prioriy : preemptive!\n");
                strcpy(run->data[0]->state, "ready");
                executed_node node_wait = {run->data[0]->pid, run->data[0]->resume_time, time, "Preemptive"};
                printf("ready : %d, run : %d", front_pq(ready_queue)->io_interval, run->data[0]->io_interval);
                record_result(RMS_result, &node_wait);

                push_pq(ready_queue, pop_queue(run), run->data[0]->io_interval);
            }
        }
        //
        // Run section
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
        if (!isEmpty_queue(run)){
            run->data[0]->remaining_time--;
            if(run->data[0]->io_remain_time == time){
                printf("Rate Monotonic Schedule Imposible!");
                executed_node node_wait = {run->data[0]->pid, 0, time, "Imposible"};
                record_result(RMS_result, &node_wait);
            }
        }

        for(int i = 0; i <=ready_queue->rear && !isEmpty_PQ(ready_queue); i++)
        {
            ready_queue->data[i]->waiting_time++;
            if(ready_queue->data[i]->io_remain_time == time){
                printf("Rate Monotonic Schedule Imposible!");
                executed_node node_wait = {run->data[0]->pid, 0, time, "Imposible"};
                record_result(RMS_result, &node_wait);
            }
        }
        for(int i = 0; i <= waiting_queue->rear && !isEmpty_PQ(waiting_queue); i++)
        {
            waiting_queue->priority_array[i]--;
            waiting_queue->data[i]->io_remain_time--;
        }
        
    }
    evaluation(p, RMS_result);

}