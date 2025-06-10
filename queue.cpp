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
    Reply reply;
    reply.success = true;

    Node* prev = nullptr;
    Node* curr = queue->head;

    // update: 동일한 key가 존재하면 value만 대체
    while (curr) {
        if (curr->item.key == item.key) {
            curr->item.value = item.value;
            reply.item = item;
            return reply;
        }
        if (curr->item.key > item.key) break;
        prev = curr;
        curr = curr->next;
    }

    // 새 노드 삽입
    Node* newNode = nalloc(item);

    if (!prev) {
        // head에 삽입
        newNode->next = queue->head;
        queue->head = newNode;
        if (!queue->tail) queue->tail = newNode;
    }
    else {
        // 중간 또는 tail에 삽입
        newNode->next = curr;
        prev->next = newNode;
        if (!curr) queue->tail = newNode;
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
