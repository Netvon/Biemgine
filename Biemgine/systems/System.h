#pragma once

#include "dlldef.h"
#include "..\entities\Entity.h"
#include "..\managers\StateManager.h"

namespace biemgine
{
    class BIEMGINE System
    {
    public:
        virtual ~System();
        virtual void before();
        virtual void before(const float deltaTime);
        virtual void update(const Entity& entity);
        virtual void update(const Entity& entity, const float deltaTime);
        virtual void after();
        virtual void after(const float deltaTime);

        virtual void onSceneSwitch() = 0;

        void setTransitionManager(const StateManager* pManager);
        const StateManager* getTransitionManager() const;

    protected:
        const StateManager* transitionManager = nullptr;
    };
}
