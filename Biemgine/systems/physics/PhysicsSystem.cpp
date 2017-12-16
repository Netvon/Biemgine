#include "stdafx.h"
#include "PhysicsSystem.h"

namespace biemgine
{
    #define RAD_TO_DEGREE (180.0f / 3.14159265358979323846264338327950288f)
    #define DEGREE_TO_RAD (3.14159265358979323846264338327950288f / 180.0f)

    PhysicsSystem::PhysicsSystem()
    {
        contactListener = new ContactListener();
        gravity = new b2Vec2(0, 0);
        world = new b2World(*gravity);
        world->SetContactListener(contactListener);
    }

    PhysicsSystem::~PhysicsSystem()
    {
        world->SetContactListener(nullptr);

        if (bodies.size() > 0) {

            for (const auto &pair : bodies) {
                world->DestroyBody(pair.second);
            }
        }

        delete contactListener;
        delete gravity;
        delete world;
    }

    void PhysicsSystem::onAddEntity(Entity & entity)
    {
        auto physics = entity.getComponent<PhysicsComponent>("physics");

        if (physics != nullptr)
        {
            PhysicsEntry physicsEntry;
            physicsEntry.entity = &entity;
            physicsEntry.physicsComponent = physics;
            physicsEntry.positionComponent = entity.getComponent<PositionComponent>("position");

            physicsEntries.push_back(std::move(physicsEntry));
        }
    }

    void PhysicsSystem::before()
    {
        for (const auto &pair : bodiesUpdated) {
            bodiesUpdated[pair.first] = false;
        }
    }

    void PhysicsSystem::update()
    {
        for (PhysicsEntry entry : physicsEntries)
        {
            if (entry.entity->getIsOnScreen() && entry.entity->isAlive())
            {
                if (bodies.find(entry.entity->getId()) == bodies.end())
                {
                    bodies.insert_or_assign(entry.entity->getId(), createBody(*entry.entity));
                }

                auto body = bodies.at(entry.entity->getId());

                if (entry.physicsComponent->getHasCustomVelocity())
                    body->SetLinearVelocity({pixelToMeter(entry.physicsComponent->getVelocity().x), pixelToMeter(entry.physicsComponent->getVelocity().y)});

                entry.positionComponent->setX(meterToPixel(body->GetPosition().x - pixelToMeter(entry.physicsComponent->getColliderW() / 2.f)));
                entry.positionComponent->setY(meterToPixel(body->GetPosition().y - pixelToMeter(entry.physicsComponent->getColliderH() / 2.f)));

                body->SetTransform(body->GetPosition(), entry.positionComponent->getRotation() * DEGREE_TO_RAD);

                body->ApplyForceToCenter({pixelToMeter(entry.physicsComponent->getForceX()), pixelToMeter(entry.physicsComponent->getForceY())}, true);
                body->ApplyLinearImpulseToCenter({pixelToMeter(entry.physicsComponent->getImpulseX()), pixelToMeter(entry.physicsComponent->getImpulseY())}, true);

                entry.physicsComponent->decreaseTimedForces();

                bodiesUpdated[entry.entity->getId()] = true;

                auto velo = body->GetLinearVelocity();
                entry.physicsComponent->setVelocity({meterToPixel(velo.x), meterToPixel(velo.y)});

                body->SetLinearDamping(entry.physicsComponent->getLinearDamping());
            }
        }
    }

    void PhysicsSystem::after()
    {
        for (auto it = bodiesUpdated.cbegin(); it != bodiesUpdated.cend();)
        {
            if (!(*it).second)
            {
                world->DestroyBody(bodies[(*it).first]);
                bodies.erase(bodies.find((*it).first));
                it = bodiesUpdated.erase(it);
            }
            else
            {
                ++it;
            }
        }

        world->Step(1.f / 40.0f, 6, 2);
    }

    b2Body* PhysicsSystem::createBody(const Entity & entity)
    {
        auto pc = entity.getComponent<PositionComponent>("position");
        auto physics = entity.getComponent<PhysicsComponent>("physics");
        auto grounded = entity.getComponent<GroundedComponent>("grounded");

        b2BodyDef newBodyDef;

        if (!physics->getIsStatic())
            newBodyDef.type = b2_dynamicBody;
        else
            newBodyDef.type = b2_staticBody;

        if (grounded != nullptr) {
            newBodyDef.fixedRotation = true;
            printf("HasGrounded - ");
        }

        newBodyDef.position.Set(
            pixelToMeter( pc->getOriginX() + physics->getColliderW() / 2.f ),
            pixelToMeter( pc->getOriginY() + physics->getColliderH() / 2.f )
        );

        newBodyDef.angle = static_cast<float>(pc->getRotation() * DEGREE_TO_RAD);
        newBodyDef.linearDamping = 0;//0.25f;

        b2Body* body = world->CreateBody(&newBodyDef);
        body->SetUserData((void*)&entity);
        b2Fixture* fixture = nullptr;

        if (physics->getShape() == RECTANGLE) {
            b2PolygonShape polygonshape;
            polygonshape.SetAsBox(
                pixelToMeter( physics->getColliderW() / 2.f ),
                pixelToMeter( physics->getColliderH() / 2.f ),
                { 0,0/*physics->getColliderW() / 2.f, physics->getColliderH() / 2.f*/ },
                0
            );

            fixture = body->CreateFixture(&polygonshape, physics->getDensity());
        }
        else if (physics->getShape() == CIRCLE) {
            b2CircleShape circleShape;
            circleShape.m_p.Set(0, 0);
            circleShape.m_radius = pixelToMeter( physics->getColliderW() / 2.0f );

            fixture = body->CreateFixture(&circleShape, physics->getDensity());
        }

        fixture->SetRestitution(0.15f);
        //fixture->SetFriction(1.f);

        auto cc = entity.getComponent<CollidableComponent>("collidable");

        if (entity.hasComponent("collidable")) {
            b2Filter filter = fixture->GetFilterData();
            filter.categoryBits = cc->getCategoryBits();
            filter.maskBits = cc->getMaskBits();
            fixture->SetFilterData(filter);
        }

        if (entity.hasComponent("grounded")) {
            b2PolygonShape groundShape;
            groundShape.SetAsBox(
                pixelToMeter(physics->getColliderW() * 0.5f),
                pixelToMeter(physics->getColliderH() * 0.5f),
                { 0, pixelToMeter(0.25f) },
                0
            );

            b2FixtureDef groundFixtureDef;
            groundFixtureDef.shape = &groundShape;
            groundFixtureDef.isSensor = true;

            b2Fixture* groundFixture = body->CreateFixture(&groundFixtureDef);

            if (entity.hasComponent("collidable")) {
                b2Filter filter = groundFixture->GetFilterData();
                filter.categoryBits = cc->getCategoryBits();
                filter.maskBits = cc->getMaskBits();
                groundFixture->SetFilterData(filter);
            }
        }

        printf("Adding body with mass: %f, density: %f\n", body->GetMass(), fixture->GetDensity());
        physics->setMass(body->GetMass());

        return body;
    }

    Vector PhysicsSystem::pixelToMeter(Vector & pixelVector)
    {
        return pixelVector / pixelsInAMeter;
    }

    float PhysicsSystem::pixelToMeter(float pixelValue)
    {
        return pixelValue / pixelsInAMeter;
    }

    Vector PhysicsSystem::meterToPixel(Vector & pixelVector)
    {
        return pixelVector * pixelsInAMeter;
    }

    float PhysicsSystem::meterToPixel(float meterValue)
    {
        return meterValue * pixelsInAMeter;
    }
}
