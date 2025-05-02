#include "pong.h"

Pong::Pong() {
    m_ball.radius = 20;
    m_ball.Reset();
    m_ball.reset_counter = 0.2;

    m_player_paddle.width = 25;
    m_player_paddle.height = 120;
    m_player_paddle.x = Constants::screen_width - m_player_paddle.width - 10;
    m_player_paddle.y = (Constants::screen_height - m_player_paddle.height) / 2.0;
    m_player_paddle.velocity = 300;

    m_cpu_paddle.width = 25;
    m_cpu_paddle.height = 120;
    m_cpu_paddle.x = 10;
    m_cpu_paddle.y = (Constants::screen_height - m_cpu_paddle.height) / 2.0;
    m_cpu_paddle.velocity = 300;

    m_player_score = 0;
    m_cpu_score = 0;
    m_paused = false;
}

void Pong::HandleInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        m_paused ^= true;
    }
}

void Pong::Draw() {
    ClearBackground(BLACK);

    m_ball.Draw();
    m_player_paddle.Draw();
    m_cpu_paddle.Draw();

    DrawText(TextFormat("%i", m_cpu_score), Constants::screen_width / 4, 20, 80, WHITE);
    DrawText(TextFormat("%i", m_player_score), 3 * Constants::screen_width / 4, 20, 80, WHITE);

    if (m_paused && DrawPauseMenu()) {
        m_paused = false;
    }

    EndDrawing();
}

void Pong::Update() {
    if (m_paused) return;

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
    x = Constants::screen_width / 2.0;
    y = Constants::screen_height / 2.0;

    int dx[2] = {-1, 1};

    vx = 350 * dx[GetRandomValue(0, 1)];
    vy = 280 * dx[GetRandomValue(0, 1)];

    reset_counter = 1.0;
}

void Pong::Ball::Update(int& player_score, int& cpu_score) {
    if (reset_counter > 0) {
        reset_counter -= GetFrameTime();
        return;
    }

    x += vx * GetFrameTime();
    y += vy * GetFrameTime();

    if (x + radius >= Constants::screen_width) {
        ++cpu_score;
        Reset();
    }
    if (x - radius <= 0) {
        ++player_score;
        Reset();
    }

    if (y + radius >= Constants::screen_height || y - radius <= 0) {
        vy *= -1;
    }
}

void Pong::PlayerPaddle::Update() {
    if (IsKeyDown(KEY_UP)) {
        y -= velocity * GetFrameTime();
    }

    if (IsKeyDown(KEY_DOWN)) {
        y += velocity * GetFrameTime();
    }

    if (y <= 0)
        y = 0;
    if (y + height >= Constants::screen_height)
        y = Constants::screen_height - height;
}

void Pong::CPUPaddle::Update(const Pong::Ball& ball) {
    if (y + height / 2.0 > ball.y) {
        y -= velocity * GetFrameTime();
    } else {
        y += velocity * GetFrameTime();
    }

    if (y <= 0)
        y = 0;
    if (y + height >= Constants::screen_height)
        y = Constants::screen_height - height;
}
