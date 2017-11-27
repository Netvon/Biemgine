#pragma once

#include "Biemgine.h"

#include "stdafx.h"
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
        std::time_t nextSaveBlobTime = 0;

        std::vector<const Entity*> entities;
    };
}
