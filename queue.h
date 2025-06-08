// queue.h
#pragma once
#include "qtype.h"

Queue* init(void);
Node* nalloc(Item item);
Reply enqueue(Queue* queue, Item item);
Reply dequeue(Queue* queue);
Queue* range(Queue* queue, Key start, Key end);
