#pragma once

#include "dlldef.h"
#include <map>
#include <iostream>
#include <cassert>
#include <vector>
#include <functional>
#include <memory>
#include <typeindex>
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

        template<typename TComponent>
        bool hasComponent() const;
        bool hasComponent(const string& name) const;
        void addComponent(const string& name, Component* component);

        template<typename TRequired>
        bool meets(TRequired& requirements);

        template <typename TComponent, typename ...TArgs>
        void addComponent(const string& name, TArgs&&...arguments);

        int getId() const;

        virtual void die() const;
        bool isAlive() const;

        bool hasTag() const;
        void setTag(string pTag);
        string getTag() const;

        Rect getBounds() const;

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

        return vec;
    }

    template<typename TComponent>
    inline bool Entity::hasComponent() const
    {
        for (auto& kv : componentHashmap) {
            auto tip = std::type_index(typeid(*kv.second));

            if (tip == std::type_index(typeid(TComponent)))
                return true;
        }

        return false;
    }

    template<typename TRequired>
    inline bool Entity::meets(TRequired & requirements)
    {
        int required_count = 0;
        int required_hit = 0;
        int optional_hit = 0;

        for (auto &req_kv : requirements) {
            if (!req_kv.optional) {
                required_count++;
            }
        }

        for (auto &kv : componentHashmap) {
            auto type = std::type_index(typeid(*kv.second));

            for (auto &req_kv : requirements) {
                if (req_kv.type == type) {

                    if (req_kv.exclude)
                        return false;

                    if (req_kv.optional) {
                        optional_hit++;
                    }
                    else {
                        required_hit++;
                    }
                }
            }
        }

        return required_hit == required_count;

        //return std::any_of(componentHashmap.begin(), componentHashmap.end(), [&requirements](const auto &kv) {
        //    auto comp_type = std::type_index(typeid(*kv.second));

        //    /*bool has_optional = std::any_of(requirements.begin(), requirements.end(), [&comp_type](const auto& r) {
        //        return r.type == comp_type && r.optional;
        //    });*/

        //    return std::all_of(requirements.begin(), requirements.end(), [&comp_type/*, &has_optional*/](const auto& r) {

        //        /*if (has_optional && r.type == comp_type && r.optional) {
        //            return false;
        //        }*/

        //        bool type_match = r.type == comp_type;

        //        if (type_match && r.exclude)
        //            return false;

        //        return type_match;
        //    });
        //});
    }

    template<typename TComponent, typename ...TArgs>
    void Entity::addComponent(const string & name, TArgs && ...arguments)
    {
        componentHashmap.emplace(std::make_pair(name, std::make_shared<TComponent>(std::forward<TArgs>(arguments)...)));
    }
}
