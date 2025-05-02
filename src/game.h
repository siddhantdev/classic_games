#pragma once
#include "raylib.h"
#include "raygui.h"
#include "conf.h"

#include <string>

class Game {
    public:
        Game() = default;

        virtual void Draw() =0;

        virtual void HandleInput() =0;

        virtual void Update() =0;

        virtual std::string getTitle() =0;

        bool DrawPauseMenu() {
            DrawRectangle(200, 220, 400, 350, RAYWHITE);

            int pause_width = MeasureText("Game Paused", 45);
            DrawText("Game Paused", (Constants::screen_width - pause_width) / 2, 300, 45, BLACK);

            int play_result = GuiButton(Rectangle{300, 370, 200, 50}, "Continue");
            int exit_result = GuiButton(Rectangle{300, 430, 200, 50}, "Exit");

            if (play_result) {
                return true;
            }

            if (exit_result) {
                CloseWindow();
            }

            return false;
        }
};
