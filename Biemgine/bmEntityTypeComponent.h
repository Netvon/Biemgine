#pragma once

#include "bmComponent.h"
#include "bmEntityType.h"

class bmEntityTypeComponent :
	public bmComponent
{
public:
    bmEntityTypeComponent(bmEntityType entityType = ENTITY)
        : entityType(entityType)
    { }

    bmEntityType getType() const
    {
        return this->entityType;
    }

    bool isType(const bmEntityType entityType) const
    {
        return this->getType() == entityType;
    }

private:
    bmEntityType entityType;
};

