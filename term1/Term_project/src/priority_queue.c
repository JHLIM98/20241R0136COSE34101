//
// Project: CPU scheduling simulator
// Author: JangHo LIM
// Affiliation: Korea University
// Date: 2024.05.30
//
#include "../include/priority_queue.h"

PriorityQueue* init_PriorityQueue(bool IsAscending)
{
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->rear = -1;
    pq->ascending = IsAscending;

    if(IsAscending){
        for(int i = 0; i < QUEUE_SIZE; i++)
        {
            if(IsAscending) pq->priority_array[i] = 0;     
            else pq->priority_array[i] = PRIORITY_MAX + 1;
        }
    }




    return pq;
}

bool isEmpty_PQ(PriorityQueue* pq)
{
    return pq->rear == -1;
}

bool isFull_PQ(PriorityQueue* pq)
{
    return pq->rear == QUEUE_SIZE - 1;
}

void push_pq(PriorityQueue* pq,  Process* p, int priority_data)
{
    if(isFull_PQ(pq)){
        printf("PUSH_PQ operation : pq is fool");
        return;
    }
    int idx = -1;
    for(int i = pq->rear; i >= 0; i--)
    {
        if((pq->ascending && priority_data < pq->priority_array[i]) ||  //ascending
           (!pq->ascending && priority_data > pq->priority_array[i]))   //descending
            {
                pq->data[i + 1] = pq -> data[i];
                pq->priority_array[i + 1] = pq->priority_array[i];
            }

        else {
            idx = i;
            break;
        }
    }

    pq->data[idx + 1] = p;
    pq->priority_array[idx + 1] = priority_data;
    pq->rear++;
}

Process* pop_pq(PriorityQueue* pq)
{
    if(isEmpty_PQ(pq)){
        printf("POP_PQ operation : pq is empty");
        return NULL;
    }
    Process* process = pq->data[0];
    for(int i = 0; i < pq->rear; i++)
    {
        pq->data[i] = pq->data[i+1];
        pq->priority_array[i] = pq->priority_array[i+1];
    }
    pq->rear--;
    return process;
}
Process* front_pq(PriorityQueue* pq)
{
    if(isEmpty_PQ(pq)){
        printf("POP_PQ operation : pq is empty");
        return NULL;
    }
    return pq->data[0];
}
void print_pq(PriorityQueue* pq)
{
    if(isEmpty_PQ(pq)){
        printf("Print_pq operation : pq is Empty\n");
        return;
    }
    
    printf("\n***  Priority Queue data => (pid : priority)  ***\n");
    for(int i = 0; i <= pq->rear; i++)
    {
        printf("(%d : %d)", pq->data[i]->pid, pq->priority_array[i]);
        if(i != pq->rear) printf(" -> ");
    }
    printf("\n\n");
}