#ifndef COUNTER_HPP
#define COUNTER_HPP

class Counter {
public:
    Counter(int mines);
    void draw(int y_offset, int font_size, int width);
    void set_flags(int flags);
private:
    int mines;
    int flags;
};

#endif