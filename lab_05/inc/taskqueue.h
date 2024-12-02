#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <mutex>

#include <queue>
#include <task.h>


template <typename T>
class TaskQueue
{
public:
    TaskQueue() {};

    void Push(const T &task) {
        std::lock_guard<std::mutex> lock(mtx_);
        queue_.push(task);
    }

    T Pop() {
        std::lock_guard<std::mutex> lock(mtx_);
        T task = queue_.front();
        queue_.pop();
        return task;
    }

    bool IsEmpty() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return queue_.empty();
    };

private:
    std::queue<T> queue_;
    mutable std::mutex mtx_;
};

#endif // TASKQUEUE_H
