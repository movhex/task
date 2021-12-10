#include <random>
#include <string>
#include <algorithm>

#include "generator.h"


Generator::Generator(void)
    : m_running(false)
{}


void Generator::run(SharedBuffer<Object> *buf)
{
    if (m_running) {
        return;
    }
    m_running = true;
    m_thread = std::thread(&Generator::routine, this, buf);
}


void Generator::stop(void)
{
    m_running = false;
    m_thread.join();
}


bool Generator::isRunning(void) const
{
    return m_running;
}


void Generator::routine(SharedBuffer<Object> *buf)
{
    std::string colors = "rgb";
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(0, 2);

    auto f = [&colors, &distr, &eng] (Object &x) {
        x = Object(colors[distr(eng)]);
    };

    while (true) {
        std::for_each(buf->begin(), buf->end(), f);
        buf->notifyDataReady();
        buf->waitDataDone();
        if (!m_running) {
            break;
        }
    }
}
