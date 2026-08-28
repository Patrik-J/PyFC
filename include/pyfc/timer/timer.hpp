#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
    public:
        Timer();

        void start();
        uint64_t currentMillis();
        uint64_t currentMicros();

    private:
        std::chrono::steady_clock::time_point start_time;

};

#endif