// This is example program to demonstrate the TSStack class usage.
#include <tsstack>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

class Worker {
public:
    static void Task(TSStack<int> *tsstack, int thread_id, int iterations) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);
        for (int i = 0; i < iterations; ++i) {
            tsstack->push(thread_id * 1000 + i);
            // Random sleep to increase chance of race
            std::this_thread::sleep_for(std::chrono::microseconds(dis(gen)));
            if (!tsstack->empty()) tsstack->pop();
        }
    }
};

int main() {
    TSStack<int> *tsstack1 = new TSStack<int>();
    int num_threads = 10;
    int iterations = 1000;
    std::vector<std::thread> threads;

    std::cout << "Initial size of tsstack: " << tsstack1->size() << std::endl;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(Worker::Task, tsstack1, i, iterations);
    }
    // wait for all threads to finish
    for (auto &t: threads) t.join();
    std::cout << "Number of threads ran: " << num_threads << std::endl;
    int exit_code = 0;
    if (!tsstack1->empty()) {
        std::cerr << "Failure: TSStack is not empty after all threads finished." << std::endl;
        std::cout << "Size of tsstack now: " << tsstack1->size() << std::endl;
        exit_code = 1;
    } else {
        std::cout << "Success: TSStack is empty after all threads finished." << std::endl;
    }
    delete tsstack1;
    return exit_code;
}