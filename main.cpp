#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "queue.h"

constexpr int NUM_THREADS = 4;
constexpr int OPS_PER_THREAD = 100000;

void producer(Queue* q, int startKey) {
    for (int i = 0; i < OPS_PER_THREAD; ++i) {
        Item item = { startKey + i, i };
        enqueue(q, item);
    }
}

void consumer(Queue* q, int ops) {
    for (int i = 0; i < ops; ++i) {
        dequeue(q);
    }
}

int main() {
    Queue* q = init();

    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;

    // 2 Producer + 2 Consumer
    threads.emplace_back(producer, q, 0);
    threads.emplace_back(producer, q, OPS_PER_THREAD);
    threads.emplace_back(consumer, q, OPS_PER_THREAD);
    threads.emplace_back(consumer, q, OPS_PER_THREAD);

    for (auto& t : threads) t.join();

    auto end_time = std::chrono::high_resolution_clock::now();

    double elapsed = std::chrono::duration<double>(end_time - start_time).count();
    int total_ops = OPS_PER_THREAD * 4;

    std::cout << "Elapsed time: " << elapsed << " seconds\n";
    std::cout << "Total operations: " << total_ops << "\n";
    std::cout << "Throughput: " << (total_ops / elapsed) << " ops/sec\n";

    release(q);
    return 0;
}
