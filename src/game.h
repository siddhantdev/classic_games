#pragma once

#include <string>

class Game {
    public:
        Game() = default;

        virtual void Draw() =0;

        virtual void HandleInput() =0;

        virtual void Update() =0;

        virtual std::string getTitle() =0;
};
