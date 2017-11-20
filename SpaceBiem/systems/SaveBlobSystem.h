#pragma once

#include "Biemgine.h"

using biemgine::System;
using biemgine::FileHandler;

#include "../factories/SaveBlobFactory.h"

namespace spacebiem
{
    class SaveBlobSystem :
        public System
    {
    public:
        SaveBlobSystem::SaveBlobSystem();
        SaveBlobSystem::~SaveBlobSystem();

        void after(const float deltaTime) override;

    private:
        SaveBlobFactory * saveBlobFactory = nullptr;
        bool savingBlob = false;
    };
}
