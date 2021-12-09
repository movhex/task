#include <string>
#include <thread>
#include <chrono>
#include <iostream>

#include "object.h"
#include "shared_buffer.h"
#include "generator.h"
#include "sorter.h"


int main(void)
{
    std::string order;

    while (1) {
        std::cout << "Enter color order (e.g. rgb): ";
        std::cin >> order;
        if (order.size() == 3 &&
            order.find('r') != std::string::npos &&
            order.find('g') != std::string::npos &&
            order.find('b') != std::string::npos)
        {
            break;
        }
    }

    std::string fname = "result.log";
    std::ofstream file(fname);
    size_t bufsize = 10;

    std::cout << "Result file: " << fname << std::endl;

    SharedBuffer<Object> buf(bufsize);
    Sorter sorter(order);
    Generator gen;
    gen.run(&buf);
    sorter.run(&buf, &file);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::string cmd;

    while (true) {
        std::cout << "Enter command [start|stop|q]: ";
        std::cin >> cmd;
        if (cmd == "start") {
            if (!gen.isRunning()) {
                gen.run(&buf);
                sorter.run(&buf, &file);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            else {
                std::cout << "Threads are already running" << std::endl;
            }
        }
        else if (cmd == "stop") {
            if (gen.isRunning()) {
                buf.reset();
                gen.stop();
                sorter.stop();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            else {
                std::cout << "Threads aren't running" << std::endl;
            }
        }
        else if (cmd == "q") {
            if (gen.isRunning()) {
                buf.reset();
                gen.stop();
                sorter.stop();
            }
            break;
        }
        else {
            std::cout << "Unknown command" << std::endl;
        }
    }

    return 0;
}
