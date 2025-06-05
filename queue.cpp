// queue.cpp
#include "queue.h"
#include "qtype.h"

Queue* init(void) {
    Queue* queue = new Queue;
    queue->head = nullptr;
    queue->tail = nullptr;
    return queue;
}