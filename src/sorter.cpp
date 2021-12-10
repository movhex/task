#include <algorithm>
#include <iterator>

#include "sorter.h"


Sorter::Sorter(const std::string &order)
    : m_running(false)
{
    m_order[order[0]] = 0;
    m_order[order[1]] = 1;
    m_order[order[2]] = 2;
}


void Sorter::run(SharedBuffer<Object> *buf, std::ostream *out)
{
    if (m_running) {
        return;
    }
    m_running = true;
    m_thread = std::thread(&Sorter::routine, this, buf, out);
}


void Sorter::stop(void)
{
    m_running = false;
    m_thread.join();
}


bool Sorter::isRunning(void) const
{
    return m_running;
}


void Sorter::routine(SharedBuffer<Object> *buf, std::ostream *out)
{
    while (true) {
        buf->waitDataReady();
        if (!m_running) {
            break;
        }
        sort(buf->begin(), buf->end());
        buf->dump(out);
        buf->notifyDataDone();
    }
}


void Sorter::sort(std::vector<Object>::iterator first,
    std::vector<Object>::iterator last)
{
    if (last <= first) {
        return;
    }

    int pivot = m_order[first->getMarker()];
    auto middle = first + 1;

    for (auto i = first + 1; i < last; ++i) {
        if (m_order[i->getMarker()] < pivot) {
            std::iter_swap(i, middle);
            ++middle;
        }
    }

    std::iter_swap(first, middle - 1);
    sort(first, middle - 1);
    sort(middle, last);
}
