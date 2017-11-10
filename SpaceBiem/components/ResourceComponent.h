#pragma once

#include "Biemgine.h"

using biemgine::Component;

namespace spacebiem
{
    class ResourceComponent :
        public Component
    {
    public:
        ResourceComponent()
        {};

        void addResource(string pName, int pAmount);
        
    private:

        map<string, int> resources;

    };
}
