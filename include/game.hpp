#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "timer.hpp"
#include "counter.hpp"

class Game {
public:
    Game(int width, int height, int mines);
    ~Game();
    void draw();
    void process();
    void show_end_menu(int width, int height, int font_size);
private:
    Board *board;
    Timer *timer;
    Counter *counter;
    int y_offset;
    int x_offset;
    int cell_size;
};

#endif