// This example uses tsqueue, a thread-safe queue implementation.
// It is expected to run without issues in parallel.

#include <tsqueue>
#include <iostream>
#include <vector>
#include <thread>

class MyClass {
    int data;
public:
    MyClass(int data) : data(data) {}
};

class Worker {
public:
    static void Task(std::shared_ptr<TSQueue<MyClass>> mytsqueue, int thread_id, int iterations) {
        for (int i = 0; i < iterations; ++i) {
            mytsqueue->emplace(thread_id * 1000 + i);
            for (int j = 0; j < 10000; ++j) { /* do nothing, just simulate delay */ }
            if (!mytsqueue->empty()) mytsqueue->pop();
        }
    }
};

int main() {
    // TSQueue is assumed to be a thread-safe queue supporting concurrent push and pop operations.
    // It is used here to safely share data between multiple threads.
        auto mytsqueue = std::make_shared<TSQueue<MyClass>>();
    int num_threads = 10;
    int iterations = 1000;
    std::vector<std::thread> mythreads;
    std::cout << "Initial queue size: " << mytsqueue->size() << std::endl;
    for (int i = 0; i < num_threads; ++i) {
        mythreads.push_back(std::thread(Worker::Task, mytsqueue, i, iterations));
    }
    // wait for all threads to finish
    for (auto &t : mythreads) t.join();
    std::cout << "Final queue size: " << mytsqueue->size() << std::endl;
    int error_code = 0;
    if (mytsqueue->size() != 0) {
        std::cerr << "Failed: tsqueue size is expected to be zero. Actual "
                  << mytsqueue->size() << "." << std::endl;
        error_code = 1;
    } else {
        std::cout << "Success: tsqueue size is zero after all operations."
                  << std::endl;
    }
    // No need to delete mytsqueue, managed by shared_ptr
    return error_code;
}