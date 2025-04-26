#pragma once

#include "game.h"
#include "raylib.h"
#include "raygui.h"

class Pong : public Game {
    public:
        Pong();

        void Draw();

        void HandleInput();

        void Update();

        inline std::string getTitle() {
            return "Pong";
        }

    protected:
        int m_player_score;
        int m_cpu_score;
    
    private:
        bool m_paused;

        class Ball {
            public:
                float x, y;
                int vx, vy;
                int radius;
                float reset_counter;

                inline void Draw() {
                    DrawCircle(x, y, radius, WHITE);
                }

                void Reset();

                void Update(int& player_score, int& cpu_score);
        };

        class PlayerPaddle {
            public:
                float x, y;
                int width, height;
                int velocity;

                inline void Draw() {
                    DrawRectangle(x, y, width, height, WHITE);
                }

                void Update();
        };

        class CPUPaddle {
            public:
                float x, y;
                int width, height;
                int velocity;

                inline void Draw() {
                    DrawRectangle(x, y, width, height, WHITE);
                }

                void Update(const Ball& ball);
        };

        Ball m_ball;
        PlayerPaddle m_player_paddle;
        CPUPaddle m_cpu_paddle;
};
