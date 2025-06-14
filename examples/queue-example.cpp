// This example uses a standard queue in multithreaded context.
// It is not thread-safe, expected to fail if run in parallel.

#include <queue>
#include <iostream>
#include <vector>
#include <thread>
#include <memory> // for std::shared_ptr

class MyClass {
    int data;
public:
    MyClass(int data) : data(data) {}
    void Print() const {
        std::cout << "MyClass data: " << data << std::endl;
    }
};

class Worker {
public:
    static void Task(std::shared_ptr<std::queue<MyClass>> myqueue, int thread_id, int iterations) {
        for (int i = 0; i < iterations; ++i) {
            myqueue->emplace(thread_id * 1000 + i);
            for (int j = 0; j < 10000; ++j) { /* do nothing, just simulate delay */ }
            if (!myqueue->empty()) myqueue->pop();
        }
    }
};

int main() {
    // queue is assumed to be a thread-safe queue supporting concurrent push and pop operations.
    // It is used here to safely share data between multiple threads.
        auto myqueue = std::make_shared<std::queue<MyClass>>();
    int num_threads = 10;
    int iterations = 1000;
    std::vector<std::thread> mythreads;
    std::cout << "Initial queue size: " << myqueue->size() << std::endl;
    for (int i = 0; i < num_threads; ++i) {
        mythreads.push_back(std::thread(Worker::Task, myqueue, i, iterations));
    }
    // wait for all threads to finish
    for (auto &t : mythreads) t.join();
    std::cout << "Final queue size: " << myqueue->size() << std::endl;
    int error_code = 0;
    if (myqueue->size() != 0) {
        std::cerr << "Failed: queue size is expected to be zero. Actual "
                  << myqueue->size() << "." << std::endl;
        error_code = 1;
    } else {
        std::cout << "Success: queue size is zero after all operations."
                  << std::endl;
    }
    // No need to delete myqueue, managed by shared_ptr
    return error_code;
}