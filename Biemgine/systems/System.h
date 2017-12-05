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

        typedef std::vector<std::type_index> required_components;

        template <typename T>
        struct requirement {
            constexpr operator std::type_index() const {
                return std::type_index(typeid(T));
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

        //virtual required_components requirements() const {};

    private:
        StateManager* stateManager = nullptr;

        int timeout;
        int timeoutCounter;

    };
}
