#include <iostream>      
#include "queue.h"      
#include "qtype.h"

int main() {
    Queue* q = init();

    Item item1 = { 5, 100 };
    Item item2 = { 2, 200 };
    Item item3 = { 8, 300 };

    enqueue(q, item1);
    enqueue(q, item2);
    enqueue(q, item3);

    for (int i = 0; i < 4; ++i) {
        Reply r = dequeue(q);
        if (r.success)
            std::cout << "Dequeued: key = " << r.item.key << "\n";
        else
            std::cout << "Queue is empty\n";
    }

    return 0;
}

Queue* sub = range(q, 3, 6);
std::cout << "\n[3,6] 범위 내 노드:\n";
while (true) {
    Reply r = dequeue(sub);
    if (!r.success) break;
    std::cout << "Key = " << r.item.key << "\n";
}
