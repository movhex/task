#ifndef SORTER_H
#define SORTER_H

#include <string>
#include <thread>
#include <atomic>
#include <unordered_map>
#include <fstream>

#include "object.h"
#include "shared_buffer.h"


class Sorter {
public:
    Sorter(const std::string &order);
    void run(SharedBuffer<Object> *buf, std::ostream *out);
    void stop(void);
    bool isRunning(void) const;
private:
    void routine(SharedBuffer<Object> *buf, std::ostream *out);
    void sort(std::vector<Object>::iterator first,
        std::vector<Object>::iterator last);
private:
    std::unordered_map<char, int> m_order;
    std::atomic<bool> m_running;
    std::thread m_thread;
}; // End of class


#endif // SORTER_H
