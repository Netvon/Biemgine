#include "ResourceComponent.h"


namespace spacebiem
{
    void ResourceComponent::addResource(string pName, int pAmount)
    {
        if (pAmount > 0) {

            if (resources.find(pName) == resources.end()) {
                resources[pName] = pAmount;
            }
            else {
                resources[pName] = resources[pName] + pAmount;
            }

        }
    }
    
}
