#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include "cell.hpp"

enum GameState {
    WIN,
    LOSE,
    PLAYING
};

class Board {
public:
    Board(int width, int height, int mines);
    ~Board();
    void draw(int screen_height, int screen_width, int offset);
    void open(int x, int y);
    void flag(int x, int y);
    void unflag(int x, int y);
    bool is_game_over();
    bool is_game_won();
    void print();

    int get_width();
    int get_height();
private:
    int width;
    int height;
    int mines;
    int closed_cells;
    bool mines_generated;
    Cell **cells;
    GameState game_state;
    void generate_mines(int _x, int _y);
    void calculate_mines_around();
    void open_mines();
};

#endif