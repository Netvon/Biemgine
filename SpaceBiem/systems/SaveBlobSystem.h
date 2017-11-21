#pragma once

#include "Biemgine.h"
#include <vector>

using biemgine::System;
using biemgine::FileHandler;

#include "../factories/SaveBlobFactory.h"

namespace spacebiem
{
    class SaveBlobSystem :
        public System
    {
    public:
        void update(const Entity& entity);
        void after(const float deltaTime) override;

    private:
        SaveBlobFactory saveBlobFactory;
        bool savingBlob = false;

        std::vector<const Entity*> entities;
    };
}
