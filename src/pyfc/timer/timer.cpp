#include "timer.hpp"

Timer::Timer() {};

void Timer::start() {
    this->start_time = std::chrono::steady_clock::now();
};

uint64_t Timer::currentMicros() {
    const auto now = std::chrono::steady_clock::now();

    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(now - this->start_time);    

    return diff.count();
};

uint64_t Timer::currentMillis() {
    const auto now = std::chrono::steady_clock::now();

    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->start_time);    

    return diff.count();
};