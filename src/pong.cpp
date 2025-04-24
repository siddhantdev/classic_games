#include "pong.h"

Pong::Pong() {
    m_ball.radius = 20;
    m_ball.Reset();

    m_player_paddle.width = 25;
    m_player_paddle.height = 120;
    m_player_paddle.x = GetScreenWidth() - m_player_paddle.width - 10;
    m_player_paddle.y = (GetScreenHeight() - m_player_paddle.height) / 2.0;
    m_player_paddle.velocity = 8;

    m_cpu_paddle.width = 25;
    m_cpu_paddle.height = 120;
    m_cpu_paddle.x = 10;
    m_cpu_paddle.y = (GetScreenHeight() - m_cpu_paddle.height) / 2.0;
    m_cpu_paddle.velocity = 8;

    m_player_score = 0;
    m_cpu_score = 0;
}

void Pong::Draw() {
    ClearBackground(BLACK);

    m_ball.Draw();
    m_player_paddle.Draw();
    m_cpu_paddle.Draw();

    DrawText(TextFormat("%i", m_cpu_score), GetScreenWidth() / 4, 20, 80, WHITE);
    DrawText(TextFormat("%i", m_player_score), 3 * GetScreenWidth() / 4, 20, 80, WHITE);

    EndDrawing();
}

void Pong::Update() {
    m_ball.Update(m_player_score, m_cpu_score);
    m_player_paddle.Update();
    m_cpu_paddle.Update(m_ball);

    // Collision Detection

    if (CheckCollisionCircleRec({m_ball.x, m_ball.y}, m_ball.radius, Rectangle{m_player_paddle.x, m_player_paddle.y, static_cast<float>(m_player_paddle.width), static_cast<float>(m_player_paddle.height)})) {
        m_ball.vx *= -1;
    }

    if (CheckCollisionCircleRec({m_ball.x, m_ball.y}, m_ball.radius, Rectangle{m_cpu_paddle.x, m_cpu_paddle.y, static_cast<float>(m_cpu_paddle.width), static_cast<float>(m_cpu_paddle.height)})) {
        m_ball.vx *= -1;
    }
}

void Pong::Ball::Reset() {
    x = GetScreenWidth() / 2.0;
    y = GetScreenHeight() / 2.0;

    int dx[2] = {-1, 1};

    vx = 7 * dx[GetRandomValue(0, 1)];
    vy = 7 * dx[GetRandomValue(0, 1)];
}

void Pong::Ball::Update(int& player_score, int& cpu_score) {
    x += vx;
    y += vy;

    if (x + radius >= GetScreenWidth()) {
        ++cpu_score;
        Reset();
    }
    if (x - radius <= 0) {
        ++player_score;
        Reset();
    }

    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
        vy *= -1;
    }
}

void Pong::PlayerPaddle::Update() {
    if (IsKeyDown(KEY_UP)) {
        y -= velocity;
    }

    if (IsKeyDown(KEY_DOWN)) {
        y += velocity;
    }

    if (y <= 0)
        y = 0;
    if (y + height >= GetScreenHeight())
        y = GetScreenHeight() - height;
}

void Pong::CPUPaddle::Update(const Pong::Ball& ball) {
    if (y + height / 2.0 > ball.y) {
        y -= velocity;
    } else {
        y += velocity;
    }

    if (y <= 0)
        y = 0;
    if (y + height >= GetScreenHeight())
        y = GetScreenHeight() - height;
}
