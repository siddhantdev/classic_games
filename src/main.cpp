#include "raylib.h"
#include "game.h"
#include "pong.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

enum Screens {
    MainMenuScreen,
    GameScreen
};

Screens curr_screen = MainMenuScreen;

void DrawMainMenu() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Classic Games", 250, 250, 45, BLACK);

    int play_result = GuiButton(Rectangle{300, 340, 200, 50}, "Play");
    int exit_result = GuiButton(Rectangle{300, 410, 200, 50}, "Exit");

    if (play_result) {
        curr_screen = GameScreen;
        return;
    }

    if (exit_result) {
        CloseWindow();
    }

    EndDrawing();
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Classic Games");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0x0000FF);

    Game* game = new Pong();

    while (!WindowShouldClose())
    {
        switch (curr_screen) {
            case MainMenuScreen:
                DrawMainMenu();
                break;
            case GameScreen:
                SetWindowTitle(game->getTitle().c_str());
                game->HandleInput();
                game->Update();
                game->Draw();
                break;
        }
    }

    CloseWindow();
    return 0;
}
