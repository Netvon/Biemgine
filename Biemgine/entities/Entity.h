#pragma once

#include "dlldef.h"
#include <map>
#include <iostream>
#include <cassert>
#include <vector>
#include <functional>

#include "..\components\Component.h"
#include "..\primitives\Primitives.h"

using std::string;
using std::pair;
using std::multimap;
using std::vector;
using std::function;

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

        template <typename TComponent, typename ...TArgs>
        void addComponent(const string& name, TArgs&&...arguments);

        int getId() const;

        virtual void die() const;
        bool isAlive() const;

        void setTag(string pTag);
        string getTag() const;

        Rect getBounds() const;

    private:
        int id;
        std::multimap<string, Component*> componentHashmap;
        mutable bool alive = true;
        string tag = "";
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

    template<typename TComponent, typename ...TArgs>
    void Entity::addComponent(const string & name, TArgs && ...arguments)
    {
        componentHashmap.emplace(std::make_pair(name, new TComponent(std::forward<TArgs>(arguments)...)));
    }
}
