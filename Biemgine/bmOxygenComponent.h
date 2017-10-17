#pragma once

#include "bmComponent.h"

class bmOxygenComponent : public bmComponent
{
public:

    bmOxygenComponent(int pOxygenMax = 800, int pOxigenDecrease = 2, int pOxygenIncrease = 1):
        oxygenAmount(pOxygenMax),
        oxygenMax(pOxygenMax),
        oxygenDecrease(pOxigenDecrease),
        oxygenIncrease(pOxygenIncrease)
    { };

    int getOxygenAmount() const;
    void setOxygenAmount(int pOxygen);

    int getOxygenMax() const;

    int getOxygenDecrease() const;
    int getOxygenIncrease() const;


private:
    int oxygenAmount;
    int oxygenMax;
    int oxygenDecrease;
    int oxygenIncrease;


};

