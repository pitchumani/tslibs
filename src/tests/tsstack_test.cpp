#include <cassert>
#include <iostream>
#include <thread>
#include <vector>

#include "../tsstack.h"

void test_basic() {
    TSStack<int> s;
    assert(s.empty());
    s.push(1);
    assert(!s.empty());
    assert(s.top() == 1);
    s.push(2);
    assert(s.size() == 2);
    assert(s.top() == 2);
    s.pop();
    assert(s.top() == 1);
    s.pop();
    assert(s.empty());
}

void test_emplace() {
    TSStack<std::string> s;
    s.emplace(5, 'a'); // "aaaaa"
    assert(s.top() == "aaaaa");
    s.emplace("hello");
    assert(s.top() == "hello");
    s.pop();
    assert(s.top() == "aaaaa");
}

void test_exceptions() {
    TSStack<int> s;
    bool caught = false;
    try { s.pop(); } catch (const std::runtime_error&) { caught = true; }
    assert(caught);
    caught = false;
    try { s.top(); } catch (const std::runtime_error&) { caught = true; }
    assert(caught);
}

void test_concurrent() {
    TSStack<int> s;
    const int nthreads = 8, nperthread = 1000;
    std::vector<std::thread> threads;
    for (int i = 0; i < nthreads; ++i) {
        threads.emplace_back([&s, nperthread, i]() {
            for (int j = 0; j < nperthread; ++j) s.push(i * nperthread + j);
        });
    }
    for (auto& t : threads) t.join();
    assert(s.size() == nthreads * nperthread);
}

int main() {
    test_basic();
    test_emplace();
    test_exceptions();
    test_concurrent();
    std::cout << "All TSStack tests passed!\n";
    return 0;
}
