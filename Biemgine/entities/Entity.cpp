#include <random>

#include "stdafx.h"
#include "..\components\Component.h"
#include "Entity.h"

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
        for (std::pair<std::string, const Component*> pair : componentHashmap) {
            delete pair.second;
        }

        componentHashmap.clear();
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
}
