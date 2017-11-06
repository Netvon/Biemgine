#pragma once

#include <map>
#include <iostream>
#include <cassert>
#include <vector>

#include "..\components\bmComponent.h"

using namespace std;
using components::bmComponent;

class bmEntity
{
public:
    bmEntity();
    virtual ~bmEntity();

    template <typename TComponent>
    TComponent getComponent(const string name) const {
        auto find = componentHashmap.equal_range(name);

        for (auto it = find.first; it != find.second; ++it) {
            return dynamic_cast<TComponent>(it->second);
        }

        return nullptr;
    }

    template <typename TComponent>
    vector<TComponent> getComponents(const string name) const {

        vector<TComponent> vec;
        auto find = componentHashmap.equal_range(name);

        for (auto it = find.first; it != find.second; ++it) {
            vec.push_back(dynamic_cast<TComponent>(it->second));
        }

        return vec;
    }

    bool hasComponent(const string name) const {
        return componentHashmap.find(name) != componentHashmap.end();
    }

    void addComponent(const string name, bmComponent* component) {
        componentHashmap.insert(pair<string, bmComponent*>(name, component));
    }

    int getId() const
    {
        return this->id;
    }

private:
    int id;
    multimap<string, bmComponent*> componentHashmap;
};
