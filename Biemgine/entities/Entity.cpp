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

    bool Entity::isAlive() const
    {
        return alive;
    }

    Rect Entity::getBounds() const
    {
        Rect rect;
        rect.hasSize = false;

        if (!hasComponent("position") || !hasComponent("texture"))
            return rect;

        auto pc = getComponent<PositionComponent>("position");
        auto tc = getComponents<TextureComponent>("texture");

        for (auto texture : tc)
        {
            int xMin = pc->getX() + texture->getOffsetX() - texture->getWidth() / 2;
            int xMax = pc->getX() + texture->getOffsetX() + texture->getWidth() / 2;
            int yMin = pc->getY() + texture->getOffsetY() - texture->getHeight() / 2;
            int yMax = pc->getY() + texture->getOffsetY() + texture->getHeight() / 2;

            if (!rect.hasSize)
            {
                rect.topLeft.x = xMin;
                rect.bottomLeft.x = xMin;
                rect.topRight.y = yMin;
                rect.topLeft.y = yMin;
                rect.bottomRight.x = xMax;
                rect.topRight.x = xMax;
                rect.bottomLeft.y = yMax;
                rect.bottomRight.y = yMax;
                rect.hasSize = true;
            }
            else
            {
                if (rect.topLeft.x > xMin)
                {
                    rect.topLeft.x = xMin;
                    rect.bottomLeft.x = xMin;
                }

                if (rect.topRight.y > yMin)
                {
                    rect.topRight.y = yMin;
                    rect.topLeft.y = yMin;
                }

                if (rect.bottomRight.x < xMax)
                {
                    rect.bottomRight.x = xMax;
                    rect.topRight.x = xMax;
                }

                if (rect.bottomLeft.y < yMax)
                {
                    rect.bottomLeft.y = yMax;
                    rect.bottomRight.y = yMax;
                }
            } 
        }

        return rect;
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
}
