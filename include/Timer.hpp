#ifndef __TIMER_HPP
#define __TIMER_HPP

#include <chrono>
#include <string>

class Timer {
    public:
        Timer() {}

        void start();
        std::string stop();

    private:
        std::chrono::high_resolution_clock::time_point start_point;

        std::string format_duration(
            const std::chrono::nanoseconds &t_duration);
};

#endif //__TIMER_HPP
