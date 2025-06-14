#include "../tsqueue.h"
#include <cassert>
#include <iostream>
#include <thread>
#include <vector>
#include <string>

void test_basic() {
    TSQueue<int> q;
    assert(q.empty());
    int a = 1, b = 2;
    q.push(a);
    assert(!q.empty());
    assert(q.front() == 1);
    q.push(b);
    assert(q.size() == 2);
    assert(q.back() == 2);
    q.pop();
    assert(q.front() == 2);
    q.pop();
    assert(q.empty());
}

void test_emplace() {
    TSQueue<std::string> q;
    q.emplace(5, 'a'); // "aaaaa"
    assert(q.front() == "aaaaa");
    q.emplace("hello");
    assert(q.back() == "hello");
    q.pop();
    assert(q.front() == "hello");
}

void test_concurrent() {
    TSQueue<int> q;
    const int nthreads = 8, nperthread = 1000;
    std::vector<std::thread> threads;
    for (int i = 0; i < nthreads; ++i) {
        threads.emplace_back([&q, nperthread, i]() {
            for (int j = 0; j < nperthread; ++j) {
                int v = i * nperthread + j;
                q.push(v);
            }
        });
    }
    for (auto& t : threads) t.join();
    assert(q.size() == nthreads * nperthread);
}

int main() {
    test_basic();
    test_emplace();
    test_concurrent();
    std::cout << "All TSQueue tests passed!\n";
    return 0;
}
