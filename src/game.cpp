#include "raylib.h"
#include "game.hpp"

Game::Game(int width, int height, int mines) {
    board = new Board(width, height, mines);
    timer = new Timer();
}

Game::~Game() {
    delete board;
}

void Game::draw() {
    board->draw(cell_size, y_offset, x_offset);

    int width = GetScreenWidth();
    int height = GetScreenHeight();

    DrawRectangle(0, 0, width, y_offset, LIGHTGRAY);
    DrawLine(0, y_offset, width, y_offset, BLACK);

    int font_size = height * 0.05;

    DrawText("R - Restart", 10, 10, font_size * 0.8, BLACK);

    timer->draw(y_offset, font_size, width);

    if (board->is_game_over()) {
        show_end_menu(width, height, font_size);
    }
}

void Game::process() {
    auto width = GetScreenWidth();
    auto height = GetScreenHeight();
    int panel_height = static_cast<int>(height * 0.12f);
    height -= panel_height;

    int cell_height = height / board->get_height();
    int cell_width = width / board->get_width();

    cell_size = cell_width < cell_height ? cell_width : cell_height;

    y_offset = panel_height + height - cell_size * board->get_height();
    x_offset = (width - cell_size * board->get_width()) / 2;

    if (IsKeyPressed(KEY_R)) {
        board->restart();
        timer->restart();
    }

    if (board->is_game_over()) {
        return;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int x = GetMouseX();
        int y = GetMouseY();

        if (y > y_offset && x > x_offset) {
            x = (x - x_offset) / cell_size;
            y = (y - y_offset) / cell_size;

            board->open(x, y);
            if (!timer->is_started()) {
                timer->start();
            }
            if (board->is_game_over()) {
                timer->stop();
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        int x = GetMouseX();
        int y = GetMouseY();

        if (y > y_offset && x > x_offset) {
            x = (x - x_offset) / cell_size;
            y = (y - y_offset) / cell_size;

            board->flag(x, y);
        }
    }
}

void Game::show_end_menu(int width, int height, int font_size) {
    DrawRectangle(0, 0, width, height, ColorAlpha(LIGHTGRAY, 0.5f));

    std::string game_status = board->is_game_won() ? "You won!" : "Game Over!";

    const char* restart_text = "Press R to restart";

    int text_width = MeasureText(restart_text, font_size);

    DrawRectangle(width / 2 - text_width / 2 - 10, height / 2 - font_size / 2 - 10, text_width + font_size * 0.5, font_size * 2.2, ColorAlpha(DARKGRAY, 0.9));

    Rectangle rec = {width / 2 - text_width / 2 - 10, height / 2 - font_size / 2 - 10, text_width + font_size * 0.5f, font_size * 2.2f};

    int line_thickness = 3;

    DrawRectangleLinesEx(rec, line_thickness, BLACK);

    if (board->is_game_won()) {
        DrawText(game_status.c_str(), width / 2 - MeasureText(game_status.c_str(), font_size) / 2, height / 2 - font_size / 2, font_size, BLACK);
    } else {
        DrawText(game_status.c_str(), width / 2 - MeasureText(game_status.c_str(), font_size) / 2, height / 2 - font_size / 2, font_size, BLACK);
    }

    DrawText(restart_text, width / 2 - MeasureText(restart_text, font_size) / 2, height / 2 + font_size / 2, font_size, BLACK);
}