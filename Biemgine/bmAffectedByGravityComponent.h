#pragma once
#include "bmComponent.h"

class bmAffectedByGravityComponent
    : public bmComponent
{
public:
    bmAffectedByGravityComponent(bool isAffected) : isAffected(isAffected) {};

    bool getIsAffected() const {
        return isAffected;
    }

private:
    bool isAffected;
};
