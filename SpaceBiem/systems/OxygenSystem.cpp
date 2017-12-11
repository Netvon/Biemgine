#include <algorithm>

#include "OxygenSystem.h"

using biemgine::PositionComponent;
using biemgine::CollidableComponent;
using biemgine::AudioComponent;

namespace spacebiem
{
    void OxygenSystem::before() {
        entitiesWithAtmospheres.clear();
        entitiesWithOxygen.clear();
    }

    void OxygenSystem::update(const Entity & entity)
    {
        if (entity.hasComponent("atmosphere")) {
            if (std::find(entitiesWithAtmospheres.begin(), entitiesWithAtmospheres.end(), entity) == entitiesWithAtmospheres.end()) {
                entitiesWithAtmospheres.push_back(entity);
            }
        }

        if (!entity.hasComponent("oxygen")) return;
        if (entity.hasComponent("ui")) return;

        entitiesWithOxygen.push_back(entity);
    }


    void OxygenSystem::after() {

        for (Entity& entity : entitiesWithOxygen) {

            auto oc = entity.getComponent<OxygenComponent>("oxygen");

            if (entity.hasComponent("position")) {
                auto pc = entity.getComponent<PositionComponent>("position");

                if (oc->getAtmosphereEntity() == nullptr)
                {
                    for (auto entity : entitiesWithAtmospheres)
                    {
                        auto ac = entity.getComponent<AtmosphereComponent>("atmosphere");

                        int xA = ac->getX();
                        int yA = ac->getY();
                        int rA = ac->getRadius();
                        int x = pc->getX();
                        int y = pc->getY();

                        // Kei skône pietjegras theorie
                        if (((x - xA)*(x - xA)) + ((y - yA)*(y - yA)) <= (rA*rA))
                        {
                            if (entity.hasComponent("audio"))
                            {
                                auto audioComponent = entity.getComponent<AudioComponent>("audio");
                                getStateManager()->getAudioDevice().playFadeInSoundEffect(audioComponent->getPath(), audioComponent->getLoops(), audioComponent->getChannel(), audioComponent->getVolume(), audioComponent->getFadeInTime());
                            }

                            oc->setAtmosphereEntity(std::make_shared<Entity>(entity));
                            break;
                        }
                    }
                }
                else
                {
                    auto ac = oc->getAtmosphereEntity()->getComponent<AtmosphereComponent>("atmosphere");;

                    int xA = ac->getX();
                    int yA = ac->getY();
                    int rA = ac->getRadius();
                    int x = pc->getX();
                    int y = pc->getY();

                    // Kei skône pietjegras theorie
                    if (!(((x - xA)*(x - xA)) + ((y - yA)*(y - yA)) <= (rA*rA)))
                    {
                        if (oc->getAtmosphereEntity()->hasComponent("audio"))
                        {
                            auto audioComponent = oc->getAtmosphereEntity()->getComponent<AudioComponent>("audio");
                            getStateManager()->getAudioDevice().fadeOutSoundEffect(audioComponent->getPath(), audioComponent->getFadeInTime());
                        }
                        
                        
                        oc->setAtmosphereEntity(nullptr);
                        break;
                    }
                }
            }

            float oAmount = oc->getOxygenAmount();
            if (oc->getAtmosphereEntity() == nullptr) {
                oAmount -= oc->getOxygenScale();
            }
            else {
                auto ac = oc->getAtmosphereEntity()->getComponent<AtmosphereComponent>("atmosphere");;
                oAmount += (ac->getOxygenModifier()*oc->getOxygenScale());
            }
            oc->setOxygenAmount(oAmount);
        } 
    }
}
