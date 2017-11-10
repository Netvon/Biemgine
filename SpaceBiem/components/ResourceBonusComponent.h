#pragma once

#include "Biemgine.h"

using biemgine::Component;

namespace spacebiem
{
    class ResourceBonusComponent :
        public Component
    {
    public:
        ResourceBonusComponent(string name, int amount) :
            name(name),
            amount(amount)
        {};

        string getName() const;
        int getAmount() const;
        void setAmount(int pAmount);

    private:

        string name;
        int amount;

    };
}
