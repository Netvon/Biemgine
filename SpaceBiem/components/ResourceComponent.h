#pragma once

#include "Biemgine.h"

using biemgine::Component;

namespace spacebiem
{
    class ResourceComponent :
        public Component
    {
    public:
        ResourceComponent(){
            addResource("metal", 5);
            addResource("diamond", 8);
        };

        void addResource(string pName, int pAmount);
        const map<string, int>& getResources() const;
        
    private:

        map<string, int> resources;

    };
}
