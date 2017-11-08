#include <random>

#include "stdafx.h"
#include "..\components\bmComponent.h"
#include "bmEntity.h"

namespace biemgine {

    bmEntity::bmEntity()
    {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1, INT_MAX);

        id = dist6(rng);
    }

    bmEntity::~bmEntity()
    {
        for (std::pair<std::string, const bmComponent*> pair : componentHashmap) {
            delete pair.second;
        }

        componentHashmap.clear();
    }
    bool bmEntity::hasComponent(const string & name) const
    {
        return componentHashmap.find(name) != componentHashmap.end();
    }

    void bmEntity::addComponent(const string & name, bmComponent * component)
    {
        componentHashmap.insert(pair<string, bmComponent*>(name, component));
    }

    int bmEntity::getId() const
    {
        return this->id;
    }
}
