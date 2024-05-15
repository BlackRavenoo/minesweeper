struct Cell {
    bool is_mine;
    bool is_open;
    bool has_flag;
    int mines_around;

    Cell();
};