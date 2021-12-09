#ifndef GENERATOR_H
#define GENERATOR_H

#include <thread>
#include <atomic>

#include "object.h"
#include "shared_buffer.h"


class Generator {
public:
    Generator(void);
    void run(SharedBuffer<Object> *buf);
    void stop(void);
    bool isRunning(void) const;
private:
    void routine(SharedBuffer<Object> *buf);
private:
    std::atomic<bool> m_running;
    std::thread m_thread;
}; // End of class


#endif // GENERATOR_H
