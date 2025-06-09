// queue.cpp
#include "queue.h"
#include "qtype.h"
#include <mutex>

static std::mutex q_mutex;

Queue* init(void) {
    Queue* q = new Queue;
    q->head = nullptr;
    q->tail = nullptr;
    return q;
}

void release(Queue* queue) {
    std::lock_guard<std::mutex> lock(q_mutex);
    Node* curr = queue->head;
    while (curr) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete queue;
}

Node* nalloc(Item item) {
    Node* node = new Node;
    node->item = item;
    node->next = nullptr;
    return node;
}

void nfree(Node* node) {
    delete node;
}

Node* nclone(Node* node) {
    if (!node) return nullptr;
    return nalloc(node->item);
}

Reply enqueue(Queue* queue, Item item) {
    std::lock_guard<std::mutex> lock(q_mutex);
    Node* newNode = nalloc(item);
    Reply reply;
    reply.success = true;

    if (!queue->head) {
        queue->head = queue->tail = newNode;
        reply.item = item;
        return reply;
    }

    // priority: smaller key first
    Node* prev = nullptr;
    Node* curr = queue->head;

    while (curr && curr->item.key <= item.key) {
        prev = curr;
        curr = curr->next;
    }

    if (!prev) {
        // insert at head
        newNode->next = queue->head;
        queue->head = newNode;
    }
    else {
        prev->next = newNode;
        newNode->next = curr;
        if (!curr) {
            queue->tail = newNode;
        }
    }

    reply.item = item;
    return reply;
}

Reply dequeue(Queue* queue) {
    std::lock_guard<std::mutex> lock(q_mutex);
    Reply reply;

    if (!queue->head) {
        reply.success = false;
        return reply;
    }

    Node* temp = queue->head;
    reply.item = temp->item;
    reply.success = true;

    queue->head = temp->next;
    if (!queue->head) queue->tail = nullptr;
    nfree(temp);
    return reply;
}

Queue* range(Queue* queue, Key start, Key end) {
    std::lock_guard<std::mutex> lock(q_mutex);
    Queue* newQueue = init();

    Node* curr = queue->head;
    Node** tailPtr = &(newQueue->head);

    while (curr) {
        if (curr->item.key >= start && curr->item.key <= end) {
            Node* copyNode = nclone(curr);
            *tailPtr = copyNode;
            tailPtr = &(copyNode->next);
        }
        curr = curr->next;
    }

    // tail 설정
    Node* tailNode = newQueue->head;
    while (tailNode && tailNode->next) {
        tailNode = tailNode->next;
    }
    newQueue->tail = tailNode;

    return newQueue;
}
