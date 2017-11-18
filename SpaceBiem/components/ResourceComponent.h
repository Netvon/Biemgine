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
            addResource("metal", 0);
            addResource("diamond", 0);
            addResource("uranium", 0);
            addResource("anti-matter", 0);
        };

        void addResource(string pName, int pAmount);
        const map<string, int>& getResources() const;
        
    private:

        map<string, int> resources;

    };
}
