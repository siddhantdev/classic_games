#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Classic Games");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(SKYBLUE);
        DrawCircle(screenWidth/2, screenHeight/2, screenWidth/10.0, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
