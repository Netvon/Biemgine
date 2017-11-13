#pragma once
#include "../../systems/System.h"
#include <Box2D/Box2D.h>
#include <vector>
#include "ContactListener.h"

namespace biemgine {

    class PhysicsSystem :
        public System
    {
    public:
        PhysicsSystem();
        ~PhysicsSystem();

        void update(const Entity& entity) override;
        void onSceneSwitch() override;
        void before() override;

        void after() override;

    private:
        b2Vec2* gravity = nullptr;
        b2World* world = nullptr;
        ContactListener* contactListener = nullptr;

        std::map<int, b2Body*> bodies;

        b2Body* createBody(const Entity & entity);
    };
}