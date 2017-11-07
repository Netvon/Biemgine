#pragma once

namespace biemgine {
    class bmInputManager
    {
    public:
        bmInputManager();

        void update();
        bool isKeyDown(const char* key) const;
        bool isKeyDown(const SDL_Scancode key) const;
    private:
        const Uint8* keyStates;
    };
}