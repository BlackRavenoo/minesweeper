#include "board.hpp"
#include "math.h"
#include "config.hpp"

Board::Board(int width, int height, int mines) {
    this->width = width;
    this->height = height;
    this->mines = mines;
    closed_cells = width * height;
    mines_generated = false;
    game_state = PLAYING;
    flags = 0;

    cells = new Cell*[height];
    for(int i = 0; i < height; i++) {
        cells[i] = new Cell[width];
    }

    mine_texture = LoadTexture("resources/mine.png");
    flag_texture = LoadTexture("resources/flag.png");
    numbers_texture = LoadTexture("resources/numbers.png");
}

void Board::restart() {
    closed_cells = width * height;
    mines_generated = false;
    game_state = PLAYING;
    flags = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cells[i][j].is_open = false;
            cells[i][j].is_mine = false;
            cells[i][j].mines_around = 0;
            cells[i][j].has_flag = false;
        }
    }
}

Board::~Board() {
    for(int i = 0; i < height; i++) {
        delete[] cells[i];
    }
    delete[] cells;

    UnloadTexture(mine_texture);
    UnloadTexture(flag_texture);
}

void Board::draw(int cell_size, int height_offset, int width_offset) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(cells[i][j].is_open) {
                if (cells[i][j].is_mine) {
                    DrawRectangle(
                        j * cell_size + width_offset,
                        i * cell_size + height_offset,
                        cell_size,
                        cell_size,
                        RED
                    );

                    DrawTextureEx(
                        mine_texture,
                        {static_cast<float>(j) * cell_size + width_offset, static_cast<float>(i) * cell_size + height_offset},
                        0,
                        static_cast<float>(cell_size) / 512,
                        WHITE
                    );
                } else {
                    DrawRectangle(
                        j * cell_size + width_offset,
                        i * cell_size + height_offset,
                        cell_size,
                        cell_size,
                        (i + j) & 1 ? OPEN_CELL_COLOR1 : OPEN_CELL_COLOR2
                    );

                    if (cells[i][j].mines_around > 0) {
                        DrawTexturePro(
                            numbers_texture,
                            {
                                static_cast<float>(cells[i][j].mines_around) * 512 - 512,
                                0,
                                512,
                                512
                            },
                            {
                                static_cast<float>(j) * cell_size + width_offset,
                                static_cast<float>(i) * cell_size + height_offset,
                                static_cast<float>(cell_size),
                                static_cast<float>(cell_size)
                            },
                            {0, 0},
                            0,
                            WHITE
                        );
                    }
                }
            } else {
                DrawRectangle(
                    j * cell_size + width_offset,
                    i * cell_size + height_offset,
                    cell_size,
                    cell_size,
                    (i + j) & 1 ? CLOSED_CELL_COLOR1 : CLOSED_CELL_COLOR2
                );

                if (cells[i][j].has_flag) {
                    DrawTextureEx(
                        flag_texture,
                        {static_cast<float>(j) * cell_size + width_offset, static_cast<float>(i) * cell_size + height_offset},
                        0,
                        static_cast<float>(cell_size) / 512.0f,
                        WHITE
                    );
                }
            }
            DrawRectangleLines(
                j * cell_size + width_offset,
                i * cell_size + height_offset,
                cell_size,
                cell_size,
                BLACK
            );
        }
    }
}

void Board::open(int x, int y, bool is_click) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }

    if (mines_generated == false) {
        generate_mines(x, y);
        calculate_mines_around();
        mines_generated = true;
    }

    if (cells[y][x].has_flag) {
        return;
    }

    if(cells[y][x].is_mine) {
        game_state = LOSE;
        open_mines();
    } else if (!cells[y][x].is_open) {
        closed_cells--;
        cells[y][x].is_open = true;

        if (closed_cells == mines) {
            game_state = WIN;
            open_mines();
        }

        if (cells[y][x].mines_around == 0) {
            open(x - 1, y - 1, false);
            open(x, y - 1, false);
            open(x + 1, y - 1, false);
            open(x - 1, y, false);
            open(x + 1, y, false);
            open(x - 1, y + 1, false);
            open(x, y + 1, false);
            open(x + 1, y + 1, false);
        }
    } else if (cells[y][x].is_open && cells[y][x].mines_around > 0 && is_click) {
        int flags_around = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (x + i < 0 || x + i >= width || y + j < 0 || y + j >= height) {
                    continue;
                }

                if (cells[y + j][x + i].has_flag) {
                    flags_around++;
                }
            }
        }

        if (flags_around == cells[y][x].mines_around) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if ((i == 0 && j == 0) ||(x + i < 0 || x + i >= width || y + j < 0 || y + j >= height)) {
                        continue;
                    }

                    if (!cells[y + j][x + i].has_flag) {
                        open(x + i, y + j, false);
                    }
                }
            }
        }
    } 
}

void Board::flag(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || cells[y][x].is_open) {
        return;
    }
    if (cells[y][x].has_flag) {
        cells[y][x].has_flag = false;
        flags -= 1;
    } else {
        cells[y][x].has_flag = true;
        flags += 1;
    }
}

bool Board::is_game_over() {
    return game_state != PLAYING;
}

bool Board::is_game_won() {
    return game_state == WIN;
}

void Board::generate_mines(int _x, int _y) {
    srand(time(NULL));

    for(int i = 0; i < mines; i++) {
        int x = rand() % width;
        int y = rand() % height;

        if (cells[y][x].is_mine || (x >= _x - 1 && y >= _y - 1 && x <= _x + 1 && y <= _y + 1)) {
            i--;
        } else {
            cells[y][x].is_mine = true;
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

int Board::get_flags() {
    return flags;
}

bool Board::is_mines_generated() {
    return mines_generated;
}