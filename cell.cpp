#include "cell.hpp"

Cell::Cell() {
    is_mine = false;
    is_open = false;
    has_flag = false;
    mines_around = 0;
}