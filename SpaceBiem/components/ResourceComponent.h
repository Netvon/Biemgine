#pragma once

#include "Biemgine.h"

using biemgine::Component;
using biemgine::FileHandler;

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

            FileParser parser;
            allResources = parser.resourcesContent();
        };

        void addResource(string pName, int pAmount);
        const map<string, int>& getResources() const;
        const map<string, int>& getAllResources() const;
    private:

        map<string, int> resources;
        map<string, int> allResources;

    };
}
