//
// Project: CPU scheduling simulator
// Author: JangHo LIM
// Affiliation: Korea University
// Date: 2024.05.30
//

#ifndef QUEUE_H
#define QUEUE_H

#include "header.h"
#include "constant.h"
#include "process.h"

typedef struct {
    Process* data[QUEUE_SIZE];
    int front;
    int rear;
} Queue;

Queue* init_Queue();
bool isEmpty_queue(Queue* q);
bool isFull_queue(Queue* q);
void push_queue(Queue* q, Process* p);
Process* pop_queue(Queue* q);
Process* front_queue(Queue* q);
void print_queue(Queue* q);
int size_queue(Queue* q);  

#endif
