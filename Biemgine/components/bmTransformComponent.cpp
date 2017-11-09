#include "bmTransformComponent.h"

namespace biemgine
{
    bmTransformComponent::bmTransformComponent(float x, float y, float rotation, float scaleX , float scaleY)
        : position(x, y, 0), rotation(rotation), scale({ scaleX, scaleY }) { }

    bmTransformComponent::~bmTransformComponent() {}

    float bmTransformComponent::getRotation() const {
        return rotation;
    }

    const bmPositionComponent & bmTransformComponent::getPosition() {
        return position;
    }

    float bmTransformComponent::getScaleX() const {
        return scale.x;
    }

    float bmTransformComponent::getScaleY() const {
        return scale.y;
    }
}
