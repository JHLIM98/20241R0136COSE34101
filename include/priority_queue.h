//
// Project: CPU scheduling simulator
// Author: JangHo LIM
// Affiliation: Korea University
// Date: 2024.05.30
//

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "header.h"
#include "constant.h"
#include "process.h"

typedef struct {
    Process* data[PRIORITY_QUEUE_SIZE];
    int rear;
    int priority_array[PRIORITY_QUEUE_SIZE];
    bool ascending;
} PriorityQueue;

PriorityQueue* init_PriorityQueue(bool IsAscending);
bool isEmpty_PQ(PriorityQueue* pq);
bool isFull_PQ(PriorityQueue* pq);
void push_pq(PriorityQueue* pq,  Process* p, int priority);
Process* pop_pq(PriorityQueue* pq);
Process* front_pq(PriorityQueue* pq);
void print_pq(PriorityQueue* pq);


#endif