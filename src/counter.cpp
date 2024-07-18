#include "raylib.h"
#include "counter.hpp"

Counter::Counter(int mines): mines(mines), flags(0) {}

void Counter::set_flags(int flags) {
    this->flags = flags;
}

void Counter::draw(int y_offset, int font_size, int width) {
    int max_text_width;
    int mines_len;

    if (mines > 99) {
        mines_len = 3;
    } else {
        mines_len = 2;
    }

    if (mines_len == 3) {
        max_text_width = MeasureText("000/000", font_size);
    } else {
        max_text_width = MeasureText("00/00", font_size);
    }

    int counter_padding = font_size * 0.1;
    int digit_spacing = font_size * 0.2;

    int h = font_size + 2 * counter_padding;
    int w = max_text_width + 4 * counter_padding;
    int y = (y_offset  - h) / 2;
    int x = width * 0.3;

    int rectangle_right = x - counter_padding + w + 2 * counter_padding + digit_spacing * 2;

    if (rectangle_right > width) {
        x -= rectangle_right - width;
    }

    DrawRectangle(x - counter_padding, y - counter_padding, w + 2 * counter_padding + digit_spacing * 2, h + 2 * counter_padding, BLACK);
    DrawRectangle(x, y, w + digit_spacing * 2, h, DARKGRAY);

    int padding_x = x + counter_padding;
    int padding_y = y + counter_padding;

    char digit[2] = "0";
    int digit_width = MeasureText(digit, font_size);

    if (mines_len == 3) {
        digit[0] = '0' + flags / 100;
        DrawText(digit, padding_x, padding_y, font_size, RED);
        padding_x += digit_width + digit_spacing;
    }

    digit[0] = '0' + flags / 10 % 10;
    DrawText(digit, padding_x, padding_y, font_size, RED);
    padding_x += digit_width + digit_spacing;

    digit[0] = '0' + flags % 10;
    DrawText(digit, padding_x, padding_y, font_size, RED);
    padding_x += digit_width + digit_spacing;

    int colon_width = MeasureText("/", font_size);
    DrawText("/", padding_x, padding_y, font_size, RED);
    padding_x += digit_width - digit_spacing * (mines_len - 1) + colon_width;

    if (mines_len == 3) {
        digit[0] = '0' + mines / 100;
        DrawText(digit, padding_x, padding_y, font_size, RED);
        padding_x += digit_width + digit_spacing;
    }

    digit[0] = '0' + mines / 10 % 10;
    DrawText(digit, padding_x, padding_y, font_size, RED);
    padding_x += digit_width + digit_spacing;

    digit[0] = '0' + mines % 10;
    DrawText(digit, padding_x, padding_y, font_size, RED);
    padding_x += digit_width + digit_spacing;
}