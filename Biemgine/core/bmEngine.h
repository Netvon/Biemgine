#pragma once

#include "..\managers\bmSceneManager.h"

namespace biemgine {

    class bmEngine
    {
    public:
        void start(const string& windowTitle);

    private:
        bmSceneManager manager;
    };
}

