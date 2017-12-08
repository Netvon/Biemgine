#include <algorithm>

#include "OxygenSystem.h"

using biemgine::PositionComponent;
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

        for (Entity entity : entitiesWithOxygen) {

            auto oc = entity.getComponent<OxygenComponent>("oxygen");

            std::shared_ptr<AtmosphereComponent> currentAtmosphere = nullptr;
            if (entity.hasComponent("position")) {
                auto pc = entity.getComponent<PositionComponent>("position");

                for (auto entity : entitiesWithAtmospheres) {
                    auto oc = entity.getComponent<AtmosphereComponent>("atmosphere");

                    int xA = oc->getX();
                    int yA = oc->getY();
                    int rA = oc->getRadius();
                    int x = pc->getX();
                    int y = pc->getY();

                    // Kei skône pietjegras theorie
                    if (((x - xA)*(x - xA)) + ((y - yA)*(y - yA)) <= (rA*rA)) {
                        if (entity.hasComponent("audio"))
                        {
                            auto ac = entity.getComponent<AudioComponent>("audio");
                            getStateManager()->getAudioDevice().playFadeInSoundEffect(ac->getPath(), ac->getLoops(), ac->getChannel(), ac->getVolume(), ac->getFadeInTime());
                        }

                        currentAtmosphere = oc;
                        break;
                    }
                }
            }

            float oAmount = oc->getOxygenAmount();
            if (currentAtmosphere == nullptr) {
                oAmount -= oc->getOxygenScale();
            }
            else {
                oAmount += (currentAtmosphere->getOxygenModifier()*oc->getOxygenScale());
            }
            oc->setOxygenAmount(oAmount);

        }
        
    }

}
