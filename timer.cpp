#include <chrono>
#include <raylib.h>
#include <string>
#include "timer.hpp"

Timer::Timer() {
    restart();
}

void Timer::restart() {
    start_time = std::chrono::high_resolution_clock::now();
    paused_time = std::chrono::high_resolution_clock::now();
    end_time = std::chrono::high_resolution_clock::now();
    started = false;
    paused = false;
}

void Timer::start() {
    started = true;
    start_time = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    end_time = std::chrono::high_resolution_clock::now();
    started = false;
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
    if (!started) {
        return std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
    }
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time).count();
}

bool Timer::is_started() {
    return started;
}

bool Timer::is_paused() {
    return paused;
}

void Timer::draw(int y_offset, int font_size, int width) {
    int seconds = get_seconds();
    int minutes = seconds / 60;
    seconds %= 60;

    int max_text_width = MeasureText("99:99", font_size);

    int timer_padding = font_size * 0.1;
    int digit_spacing = font_size * 0.2;

    int h = font_size + 2 * timer_padding;
    int w = max_text_width + 2 * timer_padding;
    int y = (y_offset  - h) / 2;
    int x = width * 0.8;

    int rectangle_right = x - timer_padding + w + 2 * timer_padding + digit_spacing * 2;

    if (rectangle_right > width) {
        x -= rectangle_right - width;
    }

    DrawRectangle(x - timer_padding, y - timer_padding, w + 2 * timer_padding + digit_spacing * 2, h + 2 * timer_padding, BLACK);
    DrawRectangle(x, y, w + digit_spacing * 2, h, DARKGRAY);

    char digit[2] = "0";
    int digit_width = MeasureText(digit, font_size);

    digit[0] = '0' + minutes / 10;
    DrawText(digit, x + timer_padding, y + timer_padding, font_size, RED);

    digit[0] = '0' + minutes % 10;
    DrawText(digit, x + timer_padding + digit_width + digit_spacing, y + timer_padding, font_size, RED);

    int colon_width = MeasureText(":", font_size);
    DrawText(":", x + timer_padding + digit_width * 2 + digit_spacing * 2, y + timer_padding, font_size, RED);

    digit[0] = '0' + seconds / 10;
    DrawText(digit, x + timer_padding + digit_width * 2 + colon_width + digit_spacing * 3, y + timer_padding, font_size, RED);

    digit[0] = '0' + seconds % 10;
    DrawText(digit, x + timer_padding + digit_width * 3 + colon_width + digit_spacing * 4, y + timer_padding, font_size, RED);
}