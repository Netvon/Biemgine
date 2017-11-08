#pragma once

#include "Biemgine.h"

using namespace biemgine;

class bmOxygenComponent :
    public bmComponent
{
public:

    bmOxygenComponent(int pOxygenMax = 2000, int pOxigenDecrease = 1, int pOxygenIncrease = 2):
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

