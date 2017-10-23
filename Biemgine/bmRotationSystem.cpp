#include "stdafx.h"
#include "bmRotationSystem.h"
#include "bmGroundedComponent.h"
#include "bmPositionComponent.h"
#include "PhysicsComponentShape.h"

void bmRotationSystem::update(const bmEntity & entity)
{
    if (!entity.hasComponent("grounded")
        || !entity.hasComponent("position"))
        return;

    auto physics = entity.getComponent<bmGroundedComponent*>("grounded");
    auto position = entity.getComponent<bmPositionComponent*>("position");

    auto body = bodies.at(entity.getId());

    b2Vec2 ding = {
        affectedByGravity->getFallingTowardsX(),
        affectedByGravity->getFallingTowardsY()
    };

    b2Vec2 target = ding - body->GetPosition();

    target.Normalize();
    target *= 12000.0f;

    float angle = atan2f(-target.x, target.y);
    body->SetTransform(body->GetPosition(), angle);

    position->setRotation(body->GetAngle() * RAD_TO_DEGREE);
}
