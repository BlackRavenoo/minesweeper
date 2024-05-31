#include "raylib.h"
#include "counter.hpp"

Counter::Counter(int mines): mines(mines), flags(0) {}

void Counter::set_flags(int flags) {
    this->flags = flags;
}

void Counter::draw(int y_offset, int font_size, int width) {
    int max_text_width = MeasureText("99/99", font_size);

    int timer_padding = font_size * 0.1;
    int digit_spacing = font_size * 0.2;

    int h = font_size + 2 * timer_padding;
    int w = max_text_width + 2 * timer_padding;
    int y = (y_offset  - h) / 2;
    int x = width * 0.3;

    int rectangle_right = x - timer_padding + w + 2 * timer_padding + digit_spacing * 2;

    if (rectangle_right > width) {
        x -= rectangle_right - width;
    }

    DrawRectangle(x - timer_padding, y - timer_padding, w + 2 * timer_padding + digit_spacing * 2, h + 2 * timer_padding, BLACK);
    DrawRectangle(x, y, w + digit_spacing * 2, h, DARKGRAY);

    char digit[2] = "0";
    int digit_width = MeasureText(digit, font_size);

    digit[0] = '0' + flags / 10;
    DrawText(digit, x + timer_padding, y + timer_padding, font_size, RED);

    digit[0] = '0' + flags % 10;
    DrawText(digit, x + timer_padding + digit_width + digit_spacing, y + timer_padding, font_size, RED);

    int colon_width = MeasureText("/", font_size);
    DrawText("/", x + timer_padding + digit_width * 2 + digit_spacing * 2, y + timer_padding, font_size, RED);

    digit[0] = '0' + mines / 10;
    DrawText(digit, x + timer_padding + digit_width * 2 + colon_width + digit_spacing * 3, y + timer_padding, font_size, RED);

    digit[0] = '0' + mines % 10;
    DrawText(digit, x + timer_padding + digit_width * 3 + colon_width + digit_spacing * 4, y + timer_padding, font_size, RED);
}