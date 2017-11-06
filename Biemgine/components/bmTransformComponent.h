#pragma once

#include <glm\glm.hpp>

#include "bmComponent.h"
#include "bmPositionComponent.h"

namespace components
{
    class bmTransformComponent :
        public bmComponent
    {
        bmTransformComponent(float x, float y, float rotation = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f)
            : position(x, y, 0), rotation(rotation), scale(scaleX, scaleY) { }

        float getRotation() const {
            return rotation;
        }

        bmPositionComponent& getPosition() {
            return position;
        }

        float getScaleX() const {
            return scale.x;
        }

        float getScaleY() const {
            return scale.y;
        }

    private:
        float rotation;
        bmPositionComponent position;
        glm::vec2 scale;
    };
}
