#pragma once

#include "bmComponent.h"
#include <glm/glm.hpp>

namespace components
{
    class bmPositionComponent :
        public bmComponent
    {
    public:

        bmPositionComponent(float x = 0, float y = 0, float z = 0, float rotation = 0.0f)
            : location(x, y, z), rotation(rotation) { };

        float getX() const;
        float getY() const;
        float getZ() const;
        float getRotation() const;

        void setX(float x);
        void setY(float y);
        void setRotation(float newRotation);

        void add(float x, float y, float z = 0) {
            location += glm::vec3(x, y, z);
        }

    private:
        glm::vec3 location;
        float rotation;
    };
}
