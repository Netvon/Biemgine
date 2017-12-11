#include <random>

#include "Entity.h"

#include "stdafx.h"
#include "..\components\Component.h"

#include "..\components\PositionComponent.h"
#include "..\components\TextureComponent.h"


namespace biemgine
{
    Entity::Entity()
    {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1, INT_MAX);

        id = dist6(rng);
    }

    Entity::~Entity()
    {
        /*for (std::pair<std::string, const Component*> pair : componentHashmap) {
            delete pair.second;
        }

        componentHashmap.clear();*/
    }

    bool Entity::hasComponent(const string & name) const
    {
        return componentHashmap.find(name) != componentHashmap.end();
    }

    void Entity::addComponent(const string & name, Component * component)
    {
        componentHashmap.insert(pair<string, Component*>(name, component));
    }

    int Entity::getId() const
    {
        return this->id;
    }

    void Entity::die() const
    {
        alive = false;
    }

    void Entity::rise() const
    {
        alive = true;
    }

    bool Entity::isAlive() const
    {
        return alive;
    }

    void Entity::calculateBounds()
    {
        if (!hasComponent("position") || !hasComponent("texture"))
            return;

        auto pc = getComponent<PositionComponent>("position");
        auto tc = getComponents<TextureComponent>("texture");

        minX = 0;
        maxX = 0;
        minY = 0;
        maxY = 0;

        for (auto& texture : tc)
        {
            int textureXMin = texture->getOffsetX();
            int textureXMax = texture->getOffsetX() + texture->getWidth();
            int textureYMin = texture->getOffsetY();
            int textureYMax = texture->getOffsetY() + texture->getHeight();

            if (textureXMin < minX)
            {
                minX = textureXMin;
            }

            if (textureXMax > maxX)
            {
                maxX = textureXMax;
            }

            if (textureYMin < minY)
            {
                minY = textureYMin;
            }

            if (textureYMax > maxY)
            {
                maxY = textureYMax;
            }
        }
    }

    float Entity::distance(const Entity & entity) const
    {
        if (!hasComponent("position") || !entity.hasComponent("position")) return 0;

        auto position = getComponent<PositionComponent>("position");
        auto entityPosition = entity.getComponent<PositionComponent>("position");

        return position->distance(*entityPosition);
    }

    void Entity::checkOCCheckable()
    {
        if (hasComponent("position") && !hasComponent("camera") && !hasComponent("ui"))
            isOCCheckable = true;
        else
            isOCCheckable = false;
    }

    bool Entity::hasTag() const
    {
        return tag.empty();
    }

    void Entity::setTag(string pTag)
    {
        tag = pTag;
    }

    string Entity::getTag() const
    {
        return tag;
    }

    bool Entity::isTag(const string & pTag) const
    {
        return getTag() == pTag;
    }
    bool Entity::isCheckable() const
    {
        return isOCCheckable;
    }
   
}
