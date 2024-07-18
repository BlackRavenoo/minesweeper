# Minesweeper

Minesweeper project is an implementation of the classic "Minesweeper" game, written in C++ using the raylib 5.0 library.

## Installation

To compile the project, you need to install the raylib library. You can do this using the following command:

### For MacOS:
```bash
brew install raylib
```

### For Ubuntu
```bash
apt-get install libraylib-dev
```

### For Fedora
```bash
dnf install raylib-devel
```

### For Arch
```bash
pacman -S raylib 
```

### For other systems:
Visit the [official raylib website](https://www.raylib.com/).

# Build and Run
The project is built using the following commands:
```bash
cmake .
make
```

To run the project, use the command:

```bash
./minesweeper
```

You can also pass arguments to the application in the form: ./minesweeper n m mines_count,where n and m are the width and height of the game board,respectively, and mines_count is the number of mines on it. The number of mines cannot be greater than n * m - 9.

### Example
```bash
./minesweeper 20 20 40
```

## Customization

You can customize the appearance of the game by changing the colors in the `config.hpp` file. Here are the variables you can adjust:

- `OPEN_CELL_COLOR1` and `OPEN_CELL_COLOR2`: Colors for opened cells.
- `CLOSED_CELL_COLOR1` and `CLOSED_CELL_COLOR2`: Colors for closed cells.