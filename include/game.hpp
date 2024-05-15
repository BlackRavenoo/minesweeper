#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "timer.hpp"

class Game {
public:
    Game(int width, int height, int mines);
    ~Game();
    void draw();
    void open(int x, int y);
    void flag(int x, int y);
    void unflag(int x, int y);
    bool is_game_over();
    bool is_game_won();
    void print();
    void process();
    void show_start_menu();
    void show_end_menu();
private:
    Board *board;
    Timer *timer;
    int y_offset;
    int x_offset;
    int cell_size;
};

#endif