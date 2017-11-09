#include "stdafx.h"
#include "bmPositionComponent.h"

namespace biemgine
{
    bmPositionComponent::bmPositionComponent(float x, float y, float z, float rotation)
        : location({ x, y, z }), rotation(rotation) { }

    bmPositionComponent::~bmPositionComponent() {}

    float bmPositionComponent::getX() const
    {
        return location.x;
    }

    float bmPositionComponent::getY() const
    {
        return location.y;
    }

    float bmPositionComponent::getZ() const
    {
        return location.z;
    }

    float bmPositionComponent::getRotation() const
    {
        return rotation;
    }

    void bmPositionComponent::setX(float x)
    {
        location.x = x;
    }

    void bmPositionComponent::setY(float y)
    {
        location.y = y;
    }

    void bmPositionComponent::setRotation(float newRotation)
    {
        rotation = newRotation;
    }
    void bmPositionComponent::add(float x, float y, float z)
    {
        location += { x, y, z };
    }
}
