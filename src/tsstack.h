#ifndef TSSTACK_H
#define TSSTACK_H

// This header file defines the Thread-Safe Stack class template.
#include <mutex>
#include <vector>
#include <stdexcept>

template <typename T>
class TSStack {
    std::vector<T> data;
    std::mutex mtx;
public:
    TSStack() = default;
    ~TSStack() = default;
    template<typename... Args>
    void emplace(Args&&... args);
    void push(const T &value);
    T top();
    void pop();
    size_t size();
    bool empty();
};

template<typename T>
template<typename... Args>
void TSStack<T>::emplace(Args&&... args) {
    std::lock_guard<std::mutex> lock(mtx);
    data.emplace_back(T(std::forward<Args>(args)...));
}

template<typename T>
bool TSStack<T>::empty() {
    std::lock_guard<std::mutex> lock(mtx);
    return data.size() == 0;
}

template<typename T>
void TSStack<T>::push(const T &value) {
    std::lock_guard<std::mutex> lock(mtx);
    data.push_back(value);
}

template<typename T>
T TSStack<T>::top() {
    std::lock_guard<std::mutex> lock(mtx);
    if (data.empty()) {
        throw std::runtime_error("Stack is empty");
    }
    auto val = data.back();
    return val;
}

template<typename T>
void TSStack<T>::pop() {
    std::lock_guard<std::mutex> lock(mtx);
    if (data.empty()) {
        throw std::runtime_error("Stack is empty");
    }
    data.pop_back();
}

template<typename T>
size_t TSStack<T>::size() {
    std::lock_guard<std::mutex> lock(mtx);
    size_t ret = data.size();
    return ret;
}

#endif // TSSTACK_H
