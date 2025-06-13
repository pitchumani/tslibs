// This is example program to demonstrate the stack class usage.
#include <stack>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

class Worker {
public:
    static void Task(std::stack<int> *mystack, int thread_id, int iterations) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);
        for (int i = 0; i < iterations; ++i) {
            mystack->push(thread_id * 1000 + i);
            // Random sleep to increase chance of race
            std::this_thread::sleep_for(std::chrono::microseconds(dis(gen)));
            if (!mystack->empty()) mystack->pop();
        }
    }
};

int main() {
    std::stack<int> *stack1 = new std::stack<int>();
    int num_threads = 10;
    int iterations = 1000;
    std::vector<std::thread> threads;

    std::cout << "Initial size of stack: " << stack1->size() << std::endl;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(Worker::Task, stack1, i, iterations);
    }
    // wait for all threads to finish
    for (auto &t : threads) t.join();
    int exit_code = 0;
    std::cout << "Number of threads ran: " << num_threads << std::endl;
    if (!stack1->empty()) {
        std::cerr << "Failure: Stack is not empty after all threads finished." << std::endl;
        std::cout << "Size of stack now: " << stack1->size() << std::endl;
        exit_code = 1;
    } else {
        std::cout << "Success: Stack is empty after all threads finished." << std::endl;
    }
    delete stack1;
    return exit_code;
}