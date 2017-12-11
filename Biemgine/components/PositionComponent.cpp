#include "stdafx.h"
#include "PositionComponent.h"

namespace biemgine
{
    PositionComponent::PositionComponent(float x, float y, float z, float rotation)
        : location({x, y, z}), offsetLocation({0, 0, 0}), rotation(rotation)
    {}

    PositionComponent::~PositionComponent() {}

    float PositionComponent::getOriginX() const
    {
        return location.x;
    }

    float PositionComponent::getOriginY() const
    {
        return location.y;
    }

    float PositionComponent::getX() const
    {
        return location.x + offsetLocation.x;
    }

    float PositionComponent::getY() const
    {
        return location.y + offsetLocation.y;
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

    void PositionComponent::setOffsetX(float x)
    {
        offsetLocation.x = x;
    }

    void PositionComponent::setOffsetY(float y)
    {
        offsetLocation.y = y;
    }

    void PositionComponent::setRotation(float newRotation)
    {
        rotation = newRotation;
    }

    void PositionComponent::add(float x, float y, float z)
    {
        location += { x, y, z };
    }

    float PositionComponent::distance(const PositionComponent & otherPosition)
    {
        return location.distance(otherPosition.getLocation());
    }

    const Vector & PositionComponent::getLocation() const
    {
        return location;
    }
}
