#include <cassert>
#include "board.hpp"
#include "raylib.h"

Board::Board(int width, int height, int mines) {
    assert(mines <= (width * height) - 1);
    
    this->width = width;
    this->height = height;
    this->mines = mines;
    closed_cells = width * height;
    game_state = PLAYING;

    cells = new Cell*[width];
    for(int i = 0; i < width; i++) {
        cells[i] = new Cell[height];
    }
}

Board::~Board() {
    for(int i = 0; i < width; i++) {
        delete[] cells[i];
    }
    delete[] cells;
}

void Board::draw(int cell_size, int height_offset, int width_offset) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(cells[i][j].is_open) {
                if (cells[i][j].is_mine) {
                    // Draw the mine
                    
                    

                } else {
                    // Draw the number of mines around


                }
            } else if (cells[i][j].has_flag) {
                // Draw the flagged cell


            } else {
                DrawRectangle(j * cell_size + width_offset, i * cell_size + height_offset, cell_size, cell_size, LIGHTGRAY);
                DrawRectangleLines(j * cell_size + width_offset, i * cell_size + height_offset, cell_size, cell_size, BLACK);
            }
        }
    }
}

void Board::open(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }


    std::cout << "Opening cell " << x << " " << y << std::endl;
    if (mines_generated == false) {
        generate_mines(x, y);
        calculate_mines_around();
        mines_generated = true;
    }

    if(cells[y][x].is_mine) {
        game_state = LOSE;
        open_mines();
    } else {
        closed_cells--;
        cells[y][x].is_open = true;

        if (closed_cells == mines) {
            game_state = WIN;
            open_mines();
        }
    }
}

void Board::flag(int x, int y) {
    // Put a flag on a cell
}

void Board::unflag(int x, int y) {
    // Remove a flag from a cell
}

bool Board::is_game_over() {
    return game_state != PLAYING;
}

bool Board::is_game_won() {
    return game_state == WIN;
}

void Board::print() {
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            if(this->cells[i][j].is_mine) {
                std::cout << "X";
            } else {
                std::cout << this->cells[i][j].mines_around;
            }
        }
        std::cout << std::endl;
    }
}

void Board::generate_mines(int _x, int _y) {
    srand(time(NULL));

    for(int i = 0; i < mines; i++) {
        int x = rand() % width;
        int y = rand() % height;

        if (cells[x][y].is_mine || (x == _x && y == _y)){
            i--;
        } else {
            cells[x][y].is_mine = true;
        }
    }
}

void Board::calculate_mines_around() {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(cells[i][j].is_mine) {
                continue;
            }

            int mines_around = 0;

            for(int k = -1; k <= 1; k++) {
                for(int l = -1; l <= 1; l++) {
                    if(i + k < 0 || i + k >= height || j + l < 0 || j + l >= width) {
                        continue;
                    }

                    if(cells[i + k][j + l].is_mine) {
                        mines_around++;
                    }
                }
            }

            cells[i][j].mines_around = mines_around;
        }
    }
}

void Board::open_mines() {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(cells[i][j].is_mine) {
                cells[i][j].is_open = true;
            }
        }
    }
}

int Board::get_width() {
    return width;
}

int Board::get_height() {
    return height;
}