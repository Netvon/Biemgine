#include "stdafx.h"
#include "PositionComponent.h"

namespace biemgine
{
    PositionComponent::PositionComponent(float x, float y, float z, float rotation)
        : location({ x, y, z }), rotation(rotation) { }

    PositionComponent::~PositionComponent() {}

    float PositionComponent::getX() const
    {
        return location.x;
    }

    float PositionComponent::getY() const
    {
        return location.y;
    }

    float PositionComponent::getZ() const
    {
        return location.z;
    }

    float PositionComponent::getRotation() const
    {
        return rotation;
    }

    void PositionComponent::setX(float x)
    {
        location.x = x;
    }

    void PositionComponent::setY(float y)
    {
        location.y = y;
    }

    void PositionComponent::setRotation(float newRotation)
    {
        rotation = newRotation;
    }
    void PositionComponent::add(float x, float y, float z)
    {
        location += { x, y, z };
    }
}
