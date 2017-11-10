#pragma once

#include "dlldef.h"
#include <map>
#include <iostream>
#include <cassert>
#include <vector>

#include "..\components\Component.h"
#include "..\primitives\Primitives.h"

using std::string;
using std::pair;
using std::multimap;
using std::vector;

namespace biemgine
{
    //class BIEMGINE componentmap : public std::multimap<string, Component*> {};

    class BIEMGINE Entity
    {
    public:
        Entity();
        virtual ~Entity();

        template <typename TComponent>
        TComponent getComponent(const string& name) const;

        template <typename TComponent>
        vector<TComponent> getComponents(const string& name) const;

        bool hasComponent(const string& name) const;

        void addComponent(const string& name, Component* component);

        int getId() const;

        Size getBounds() const;

    private:
        int id;
        std::multimap<string, Component*> componentHashmap;
    };

    template<typename TComponent>
    TComponent Entity::getComponent(const string & name) const
    {
        auto find = componentHashmap.equal_range(name);

        for (auto it = find.first; it != find.second; ++it) {
            return dynamic_cast<TComponent>(it->second);
        }

        return nullptr;
    }

    template<typename TComponent>
    vector<TComponent> Entity::getComponents(const string & name) const
    {
        vector<TComponent> vec;
        auto find = componentHashmap.equal_range(name);

        for (auto it = find.first; it != find.second; ++it) {
            vec.push_back(dynamic_cast<TComponent>(it->second));
        }

        return vec;
    }
}
