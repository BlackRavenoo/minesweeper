#include <raylib.h>
#include "game.hpp"
#include "timer.hpp"

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    Timer timer;

    SetWindowIcon(LoadImage("resourses/mine32.png"));

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    int n = 10;
    int mines = 10;

    float square_size = screenWidth / n;

    Game game(n, n, mines);

    while (!WindowShouldClose()) {
        // Update your variables here
        //----------------------------------------------------------------------------------
        

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        game.process();

        game.draw();

        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < n; j++) {
        //         DrawRectangle(i * square_size, j * square_size + 100, square_size, square_size, LIGHTGRAY);
        //         DrawRectangleLines(i * square_size, j * square_size + 100, square_size, square_size, BLACK);
        //     }
        // }

        //timer.draw();

        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}