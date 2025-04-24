#include "raylib.h"
#include "game.h"
#include "pong.h"

using namespace std;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Classic Games");
    SetTargetFPS(60);

    Game* game = new Pong();

    while (!WindowShouldClose())
    {
        game->HandleInput();
        game->Update();
        game->Draw();
    }

    CloseWindow();
    return 0;
}
