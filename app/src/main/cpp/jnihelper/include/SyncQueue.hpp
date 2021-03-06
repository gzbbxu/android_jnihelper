//
// Created by gzbbxu on 2019/3/31.
//

#ifndef JNIDEMO_SYNCQUEUE_H
#define JNIDEMO_SYNCQUEUE_H

#include <list>
#include <mutex>
#include <condition_variable>
#include <iostream>

template<typename T>
class SyncQueue {
private:
    bool IsFull() const {
        return m_queue.size() == m_maxSize;
    }

    bool IsEmpty() const {
        return m_queue.empty();
    }

public:
    SyncQueue(int maxSize) : m_maxSize(maxSize) {
    }

    void Put(const T &x) {
        if (IsFull()) {
            return; //add by zkk 如果满了，丢弃
        }
        std::lock_guard<std::mutex> locker(m_mutex);

        while (IsFull()) {
            std::cout << "the blocking queue is full,waiting..." << std::endl;
            m_notFull.wait(m_mutex);
        }
        m_queue.push_back(x);
        m_notEmpty.notify_one();
    }

    void Take(T &x) {
        std::lock_guard<std::mutex> locker(m_mutex);

        while (IsEmpty()) {
            std::cout << "the blocking queue is empty,wating..." << std::endl;
            m_notEmpty.wait(m_mutex);
        }

        x = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
    }

    void clear(){
        m_notEmpty.notify_one();
        m_notFull.notify_one();

        m_queue.clear();

    }

private:
    std::list<T> m_queue;                  //缓冲区
    std::mutex m_mutex;                    //互斥量和条件变量结合起来使用
    std::condition_variable_any m_notEmpty;//不为空的条件变量
    std::condition_variable_any m_notFull; //没有满的条件变量
    int m_maxSize;
};

#endif //JNIDEMO_SYNCQUEUE_H
