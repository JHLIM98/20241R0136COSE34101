#include "../include/algorithm.h"


void set_new_queue(Process* p[], PriorityQueue* new_queue) {
    for(int i = 0; i < PROCESS_COUNT; i++) {
        if (p[i] == NULL) {
            break;
        }
        push_pq(new_queue, p[i], p[i]->arrived_time);
    }
}
