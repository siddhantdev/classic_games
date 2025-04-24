#include <string>

class Game {
    public:
        Game();

        void Draw();

        void HandleInput();

        void Update();

        std::string getTitle();
};
