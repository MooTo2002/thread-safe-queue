#include "queue.h"
#include "qtype.h"

// 큐 초기화 함수: 빈 큐를 생성하고 head, tail을 nullptr로 설정
Queue* init(void) {
    Queue* queue = new Queue;
    queue->head = nullptr;
    queue->tail = nullptr;
    return queue;
}

// 노드 할당 함수: 새로운 노드를 생성하고 item 값을 넣음
Node* nalloc(Item item) {
    Node* node = new Node;
    node->item = item;
    node->next = nullptr;
    return node;
}

// 우선순위 큐 삽입 함수: key 기준 오름차순 정렬 유지
Reply enqueue(Queue* queue, Item item) {
    Node* newNode = nalloc(item); // 새로운 노드 생성
    Reply reply;
    reply.success = true;

    // 큐가 비어있는 경우 → 바로 삽입
    if (!queue->head) {
        queue->head = queue->tail = newNode;
        reply.item = item;
        return reply;
    }

    // 현재 노드를 순회하면서 삽입 위치 찾기
    Node* prev = nullptr;
    Node* curr = queue->head;

    // key가 작거나 같은 노드를 넘겨가며 삽입 지점 탐색
    while (curr && curr->item.key <= item.key) {
        prev = curr;
        curr = curr->next;
    }

    if (!prev) {
        // 맨 앞에 삽입해야 하는 경우 (head 갱신)
        newNode->next = queue->head;
        queue->head = newNode;
    } else {
        // 중간 또는 맨 끝 삽입
        prev->next = newNode;
        newNode->next = curr;

        // 맨 끝에 삽입된 경우 tail 포인터도 갱신
        if (!curr) queue->tail = newNode;
    }

    reply.item = item;
    return reply;
}
