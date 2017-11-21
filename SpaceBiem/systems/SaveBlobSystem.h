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

        void after(const float deltaTime) override;

    private:
        SaveBlobFactory saveBlobFactory;
        bool savingBlob = false;
    };
}
