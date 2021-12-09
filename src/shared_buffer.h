#ifndef SHARED_BUFFER_H
#define SHARED_BUFFER_H

#include <vector>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <iostream>


template <typename T>
class SharedBuffer : public std::vector<T> {
public:
    SharedBuffer(size_t size);
    void notifyDataReady(void);
    void waitDataReady(void);
    void notifyDataDone(void);
    void waitDataDone(void);
    void reset(void);
    void dump(std::ostream *out);
private:
    std::condition_variable m_consumer;
    std::condition_variable m_producer;
    std::mutex m_mutex_consumer;
    std::mutex m_mutex_producer;
    std::atomic<bool> m_data_ready;
    std::atomic<bool> m_data_done;
    std::atomic<bool> m_discard;
}; // End of class


template <typename T>
SharedBuffer<T>::SharedBuffer(size_t size)
    : std::vector<T>(size)
    , m_data_ready(false)
    , m_data_done(false)
    , m_discard(false)
{}


template <typename T>
void SharedBuffer<T>::notifyDataReady(void)
{
    std::lock_guard<std::mutex> lock(m_mutex_consumer);
    m_data_ready = true;
    m_discard = false;
    m_consumer.notify_one();
}


template <typename T>
void SharedBuffer<T>::waitDataReady(void)
{
    std::unique_lock<std::mutex> lock(m_mutex_consumer);
    m_consumer.wait(lock, [this] () {
        return (m_data_ready || m_discard) ? true : false; });
    if (m_discard) {
        return;
    }
    m_data_ready = false;
}


template <typename T>
void SharedBuffer<T>::notifyDataDone(void)
{
    std::lock_guard<std::mutex> lock(m_mutex_producer);
    m_data_done = true;
    m_producer.notify_one();
}


template <typename T>
void SharedBuffer<T>::waitDataDone(void)
{
    std::unique_lock<std::mutex> lock(m_mutex_producer);
    m_producer.wait(lock, [this] () {
        return (m_data_done || m_discard) ? true : false; });
    if (m_discard) {
        return;
    }
    m_data_done = false;
}


template <typename T>
void SharedBuffer<T>::reset(void)
{
    m_discard = true;
    m_data_ready = false;
    m_data_done = false;
    m_producer.notify_one();
    m_consumer.notify_one();
}


template <typename T>
void SharedBuffer<T>::dump(std::ostream *out)
{
    for (const auto &x : *this) {
        *out << x.getMarker();
    }
    *out << std::endl;
}

#endif // SHARED_BUFFER_H
