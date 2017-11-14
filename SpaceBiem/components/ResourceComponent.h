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
            addResource("metal", 51);
            addResource("diamond", 18);
            addResource("uranium", 7);
            addResource("anti-matter", 0);
        };

        void addResource(string pName, int pAmount);
        const map<string, int>& getResources() const;
        
    private:

        map<string, int> resources;

    };
}
