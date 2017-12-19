#pragma once
#include <Box2D/Box2D.h>
#include <random>
#include <math.h>
#include "ContactListener.h"

#include "../../systems/System.h"
#include "../../components/PositionComponent.h"
#include "../../components/PhysicsComponent.h"
#include "../../components/GroundedComponent.h"
#include "../../components/CollidableComponent.h"

using std::map;
using std::string;

namespace biemgine
{
    class PhysicsSystem :
        public System
    {
    public:
        struct PhysicsEntry
        {
            Entity* entity;
            std::shared_ptr<PositionComponent> positionComponent;
            std::shared_ptr<PhysicsComponent> physicsComponent;
        };

        PhysicsSystem();
        ~PhysicsSystem();

        void onAddEntity(Entity& entity) override;
        void before() override;
        void update() override;
        void after() override;

    private:
        b2Vec2* gravity = nullptr;
        b2World* world = nullptr;
        ContactListener* contactListener = nullptr;

        std::map<int, b2Body*> bodies;
        std::map<int, bool> bodiesUpdated;

        b2Body* createBody(const Entity & entity);

        float pixelsInAMeter = 100;

        Vector pixelToMeter(Vector& pixelVector);
        float pixelToMeter(float pixelValue);

        Vector meterToPixel(Vector& pixelVector);
        float meterToPixel(float meterValue);

        vector<PhysicsEntry> physicsEntries;
    };
}
