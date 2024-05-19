#include "raylib.h"
#include "game.hpp"
#include "timer.hpp"

int main(int argc, char* argv[]) {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    int n = 10;
    int m = 10;
    int mines = 10;

    if (argc == 4) {
        n = atoi(argv[1]);
        m = atoi(argv[2]);
        mines = atoi(argv[3]);
    }

    if (mines > (n * m) - 9) {
        std::cout << "Too many mines!" << std::endl;
        exit(1);
    }

    SetWindowIcon(LoadImage("resources/icon32.png"));

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "Minesweeper");
    
    Game game(n, m, mines);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        game.process();

        game.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}