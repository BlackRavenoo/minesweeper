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

    DrawRectangle(0, 0, GetScreenWidth(), y_offset, LIGHTGRAY);
    DrawLine(0, y_offset, GetScreenWidth(), y_offset, BLACK);

    timer->draw(y_offset);
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

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int x = GetMouseX();
        int y = GetMouseY();

        std::cout << "Mouse clicked at " << x << " " << y << std::endl;

        if (y > y_offset) {

            x = (x - x_offset) / cell_size;
            y = (y - y_offset) / cell_size;

            open(x, y);
        }
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        int x = GetMouseX();
        int y = GetMouseY();

        if (y > y_offset) {
            x = (x - x_offset) / cell_size;
            y = (y - y_offset) / cell_size;

            flag(x, y);
        }
    }
}

void Game::open(int x, int y) {
    board->open(x, y);
}

void Game::flag(int x, int y) {
    board->flag(x, y);
}

void Game::unflag(int x, int y) {
    board->unflag(x, y);
}

bool Game::is_game_over() {
    return board->is_game_over();
}

bool Game::is_game_won() {
    return board->is_game_won();
}

void Game::print() {
    board->print();
}

