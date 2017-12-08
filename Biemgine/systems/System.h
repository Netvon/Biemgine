#pragma once

#include "dlldef.h"
#include "..\entities\Entity.h"
#include "..\managers\StateManager.h"

#include <typeindex>

namespace biemgine
{
    class BIEMGINE System
    {
    public:
        struct build_requirement {
            std::type_index type;
            bool optional;
            bool exclude;

            build_requirement(std::type_index type, bool optional, bool exclude)
                :type(type), optional(optional), exclude(exclude)
            { }
        };

        typedef std::vector<build_requirement> required_components;
        typedef std::vector<std::string> tag_requests;

        struct optional {};
        struct required {};
        struct exclude {};

        template <typename T, typename R = System::required>
        struct requirement {

            constexpr operator build_requirement() const {
                return { std::type_index(typeid(T)), optional(), exclude() };
            }

            constexpr bool optional() const {
                return typeid(R) == typeid(System::optional);
            }

            constexpr bool exclude() const {
                return typeid(R) == typeid(System::exclude);
            }
        };

        virtual ~System();
        virtual void before();
        //virtual void before(const float deltaTime);
        virtual void update(const Entity& entity);
        virtual void update(const Entity& entity, const float deltaTime);
        virtual void after();
        virtual void after(const float deltaTime);

        virtual void onSceneSwitch() {};

        void setStateManager(StateManager* pManager);
        StateManager* getStateManager();

        void setTimeout(int pTimeout);
        inline void nextUpdate();
        bool hasTimedOut();

        virtual required_components requirements() const = 0;
        virtual tag_requests request_tags() const {
            return tag_requests();
        };

        Entity* getRequestedEntity(std::string tag) {

            if (requested_entities.count(tag) <= 0llu)
                return nullptr;

            return requested_entities.at(tag);
        }

        void setRequestedEntity(std::string tag, Entity* entity) {
            requested_entities.emplace(tag, entity);
        }

    private:
        StateManager* stateManager = nullptr;

        int timeout;
        int timeoutCounter;

    private:
        std::map<std::string, Entity*> requested_entities;

    };
}
