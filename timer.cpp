#include <chrono>
#include <raylib.h>
#include <string>
#include "timer.hpp"


Timer::Timer() {
    start_time = std::chrono::high_resolution_clock::now();
    paused_time = std::chrono::high_resolution_clock::now();
    end_time = std::chrono::high_resolution_clock::now();
    started = false;
    paused = false;
}

void Timer::start() {
    start_time = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    end_time = std::chrono::high_resolution_clock::now();
}

void Timer::reset() {
    start_time = std::chrono::high_resolution_clock::now();
}

void Timer::pause() {
    paused_time = std::chrono::high_resolution_clock::now();
}

void Timer::unpause() {
    start_time += std::chrono::high_resolution_clock::now() - paused_time;
}

int Timer::get_ticks() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
}

int Timer::get_seconds() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time).count();
}

bool Timer::is_started() {
    return start_time.time_since_epoch().count() != 0;
}

bool Timer::is_paused() {
    return paused_time.time_since_epoch().count() != 0;
}

void Timer::draw() {
    int currentTime = get_seconds();
    DrawText(std::to_string(currentTime).c_str(), 10, 10, 20, LIGHTGRAY);
}