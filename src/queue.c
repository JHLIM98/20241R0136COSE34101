//
// Project: CPU scheduling simulator
// Author: JangHo LIM
// Affiliation: Korea University
// Date: 2024.05.30
//

#include "../include/queue.h"

Queue* init_Queue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

bool isEmpty_queue(Queue* q)
{
    return ((q->front) == -1);
}

bool isFull_queue(Queue* q)
{
    return ((q->rear + 1) %QUEUE_SIZE == q->front);
}
void push_queue(Queue* q, Process *p)
{
    if(isFull_queue(q)){
        printf("PUSH operation : queue is full\n");
        return; 
    }

    q->rear = (q->rear + 1)% QUEUE_SIZE;
    q->data[q->rear] = p;

    if(isEmpty_queue(q)){
        q->front = q->rear;
    }
}

Process* pop_queue(Queue* q)
{
    if(isEmpty_queue(q)){
        printf("POP Operation : queue is Empty\n");
        return NULL;
    }
    
    Process* p = q->data[q->front];

    if(q->front == q->rear){
        q->front = -1;
        q->rear = -1;
    }
    else{
        q->front = (q->front + 1) % QUEUE_SIZE;
    }

    return p;
}
Process* front_queue(Queue* q)
{
    if(isEmpty_queue(q)){
        printf("Front Operation : queue is Empty\n");
        return NULL;
    }
    return q->data[q->front];
}
void print_queue(Queue* q)
{
    if(isEmpty_queue(q)){
        printf("Print_operation : Queue is Empty\n");
        return;
    }
    int idx = q->front;
    printf("\n***Queue data***\n");
    while(1)
    {
        printf("%d", q->data[idx]->pid);
        idx = (idx + 1) % QUEUE_SIZE;
        if(idx == (q->rear+1) % QUEUE_SIZE){
            break;
        }
        printf(" -> ");
    }

     printf("\n***Queue data : End***\n");
}


int size_queue(Queue* q)
{
    if (isEmpty_queue(q)) {
        return 0;
    }
    if (q->rear >= q->front) {
        return q->rear - q->front + 1;
    } 
    else {
        return QUEUE_SIZE - q->front + q->rear + 1;
    }
}