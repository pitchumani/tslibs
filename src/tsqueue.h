#ifndef TSQUEUE_H
#define TSQUEUE_H

#include <vector>
#include <mutex>

template<typename value_type>
class TSQueue {
    std::vector<value_type> data;
    std::mutex mtx;

public:
    TSQueue() = default;
    ~TSQueue() = default;

    // Functions are not defined as const even for non-modifying ones,
    // as mutex variable is modifed by them to get lock (thread safety)

    value_type& back() {
        std::lock_guard<std::mutex> lock(mtx);
        return data.back();
    }
    template<class... Args>
    void emplace(Args&&... args) {
        std::lock_guard<std::mutex> lock(mtx);
        data.emplace_back(value_type(std::forward<Args>(args)...));
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx);
        return data.empty();
    }

    value_type& front() {
        std::lock_guard<std::mutex> lock(mtx);
        if (data.empty()) throw std::runtime_error("TSQueue is empty!")
        return data.front();
    }

    void pop() {
        std::lock_guard<std::mutex> lock(mtx);
        if (data.empty()) throw std::runtime_error("TSQueue is empty!");
        data.erase(data.begin());
    }

    void push(const value_type& value) {
        std::lock_guard<std::mutex> lock(mtx);
        data.push_back(value);
    }

    size_t size() {
        std::lock_guard<std::mutex> lock(mtx);
        return data.size();
    }
};

#endif // TSQUEUE_H
