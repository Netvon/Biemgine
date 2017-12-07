#pragma once

#include "dlldef.h"
#include <map>
#include <iostream>
#include <cassert>
#include <vector>
#include <functional>
#include <memory>

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
        std::shared_ptr<TComponent> getComponent(const string& name) const;

        template <typename TComponent>
        vector<std::shared_ptr<TComponent>> getComponents(const string& name) const;

        bool hasComponent(const string& name) const;

        void addComponent(const string& name, Component* component);

        template <typename TComponent, typename ...TArgs>
        void addComponent(const string& name, TArgs&&...arguments);

        int getId() const;

        bool operator==(Entity entity) { return id == entity.id; }

        virtual void die() const;
        virtual void rise() const;
        bool isAlive() const;

        bool hasTag() const;
        void setTag(string pTag);
        string getTag() const;
        bool isTag(const string & pTag) const;

        void calculateBounds();
       
        int minX;
        int maxX;
        int minY;
        int maxY;

        float distance(const Entity & entity) const;

    private:
        int id;
        std::multimap<string, std::shared_ptr<Component>> componentHashmap;
        mutable bool alive = true;

        string tag;
    };

    template<typename TComponent>
    std::shared_ptr<TComponent> Entity::getComponent(const string & name) const
    {
        auto find = componentHashmap.equal_range(name);

        for (auto it = find.first; it != find.second; ++it) {
            return std::dynamic_pointer_cast<TComponent>(it->second);
        }

        return nullptr;
    }

    template<typename TComponent>
    vector<std::shared_ptr<TComponent>> Entity::getComponents(const string & name) const
    {
        vector<std::shared_ptr<TComponent>> vec;
        auto find = componentHashmap.equal_range(name);

        for (auto it = find.first; it != find.second; ++it) {
            vec.push_back(std::dynamic_pointer_cast<TComponent>(it->second));
        }

        return std::move(vec);
    }

    template<typename TComponent, typename ...TArgs>
    void Entity::addComponent(const string & name, TArgs && ...arguments)
    {
        componentHashmap.emplace(std::make_pair(name, std::make_shared<TComponent>(std::forward<TArgs>(arguments)...)));
    }
}
