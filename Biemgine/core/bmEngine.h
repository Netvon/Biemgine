#pragma once

#include "..\managers\bmSceneManager.h"

namespace core {

    class bmEngine
    {
    public:
        void start(const string& windowTitle);

    private:
        bmSceneManager manager;
    };
}

