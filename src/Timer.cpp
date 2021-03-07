#include <chrono>
#include <sstream>

#include "Timer.hpp"

using ns  = std::chrono::nanoseconds;
using hrc = std::chrono::high_resolution_clock;

std::string Timer::format_duration(const ns &t_duration) {
    std::stringstream retval;
    retval.imbue(std::locale(""));
    retval.setf(std::ios::fixed, std::ios::floatfield);
    retval.setf(std::ios::showpoint);
    retval.precision(2);

    uint64_t count = t_duration.count();

    if(count < 1'000) {
        retval << count << "ns";
    }
    else if(count < 1'000'000) {
        retval.precision(2);
        retval << count/1'000.0 << "us";
    }
    else if(count < 1'000'000'000) {
        retval << count/1'000'000.0 << "ms";
    }
    else {
        retval << count/1'000'000'000.0 << "s";
    }

    return retval.str();
}

void Timer::start() {
    start_point = hrc::now();
}

std::string Timer::stop() {
    auto duration = hrc::now() - start_point;
    return format_duration(duration);
}

