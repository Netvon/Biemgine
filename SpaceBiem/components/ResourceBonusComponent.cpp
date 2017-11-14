#include "ResourceBonusComponent.h"


namespace spacebiem
{
    string ResourceBonusComponent::getName() const
    {
        return name;
    }
    int ResourceBonusComponent::getAmount() const
    {
        return amount;
    }
    void ResourceBonusComponent::setAmount(int pAmount)
    {
        if (pAmount >= 0) {
            amount = pAmount;
        }
    }
}
