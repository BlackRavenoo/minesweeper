#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
public:
    Timer();
    void start();
    void stop();
    void reset();
    void pause();
    void unpause();
    int get_ticks();
    int get_seconds();
    bool is_started();
    bool is_paused();

    void draw();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> paused_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
    bool started;
    bool paused;
};

#endif