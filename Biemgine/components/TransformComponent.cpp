#include "TransformComponent.h"

namespace biemgine
{
    TransformComponent::TransformComponent(float x, float y, float rotation, float scaleX , float scaleY)
        : position(x, y, 0), rotation(rotation), scale({ scaleX, scaleY }) { }

    TransformComponent::~TransformComponent() {}

    float TransformComponent::getRotation() const {
        return rotation;
    }

    const PositionComponent & TransformComponent::getPosition() {
        return position;
    }

    float TransformComponent::getScaleX() const {
        return scale.x;
    }

    float TransformComponent::getScaleY() const {
        return scale.y;
    }
}
