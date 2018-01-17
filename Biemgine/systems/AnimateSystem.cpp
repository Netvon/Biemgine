#include "AnimateSystem.h"

void biemgine::AnimateSystem::onAddEntity(Entity & entity)
{
    auto ac = entity.getComponents<AnimationComponent>("animation");

    for (const auto& animation : ac)
    {
        AnimateEntry animateEntry;
        animateEntry.entity = &entity;
        animateEntry.animateComponent = animation;

        animateEntries.push_back(std::move(animateEntry)); 
    } 
}

void biemgine::AnimateSystem::update(const float deltaTime)
{
    for (const auto& entry : animateEntries)
    {
        entry.animateComponent->update(deltaTime);
    }
}
