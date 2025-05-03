#include "raylib.h"
#include "game.h"
#include "pong.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

Screens curr_screen = MainMenuScreen;

void DrawMainMenu() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    int title_width = MeasureText("Classic Games", 45);
    DrawText("Classic Games", (Constants::screen_width - title_width) / 2, 300, 45, BLACK);

    int play_result = GuiButton(Rectangle{300, 370, 200, 50}, "Play");
    int exit_result = GuiButton(Rectangle{300, 430, 200, 50}, "Exit");

    if (play_result) {
        curr_screen = GameScreen;
        return;
    }

    if (exit_result) {
        curr_screen = ExitScreen;
        return;
    }

    EndDrawing();
}

int main(void)
{
    InitWindow(Constants::screen_width, Constants::screen_height, "Classic Games");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0x0000FF);

    Game* game = new Pong(curr_screen);

    while (!WindowShouldClose() && curr_screen != ExitScreen)
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
            default:
                  break;
        }
    }

    CloseWindow();
    return 0;
}
