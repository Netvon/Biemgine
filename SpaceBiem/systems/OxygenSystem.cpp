#include <algorithm>

#include "OxygenSystem.h"

using biemgine::PositionComponent;
using biemgine::AudioComponent;

namespace spacebiem
{
    void OxygenSystem::update(const Entity & entity)
    {
        if (entity.hasComponent("atmosphere")) {
            if (std::find(entitiesWithAtmospheres.begin(), entitiesWithAtmospheres.end(), entity) == entitiesWithAtmospheres.end()) {
                entitiesWithAtmospheres.push_back(entity);
            }
        }

        /*if (entity.hasComponent("texture")) {
            auto textures = entity.getComponents<biemgine::TextureComponent*>("texture");
            for (auto tex : textures) {
                if (tex->getTag() == "clouds") {
                    tex->setRotation(tex->getRotation() + 0.01f);
                }
            }
        }*/

        if (!entity.hasComponent("oxygen") || !entity.hasComponent("position")) return;
        if (entity.hasComponent("ui")) return;

        auto oc = entity.getComponent<OxygenComponent>("oxygen");
        auto pc = entity.getComponent<PositionComponent>("position");

        if (currentAtmosphereEntity == nullptr) {
           

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

                    currentAtmosphereEntity = std::make_shared<Entity>(entity);
                    break;
                }
            }
        }
        else
        {
            auto oc = currentAtmosphereEntity->getComponent<AtmosphereComponent>("atmosphere");

            int xA = oc->getX();
            int yA = oc->getY();
            int rA = oc->getRadius();
            int x = pc->getX();
            int y = pc->getY();

            if (!(((x - xA)*(x - xA)) + ((y - yA)*(y - yA)) <= (rA*rA)))
            {
                if (currentAtmosphereEntity->hasComponent("audio"))
                {
                    auto ac = currentAtmosphereEntity->getComponent<AudioComponent>("audio");
                    getStateManager()->getAudioDevice().fadeOutSoundEffect(ac->getPath(), ac->getFadeInTime());
                }

                currentAtmosphereEntity = nullptr;
            }
        }

        float oAmount = oc->getOxygenAmount();
        if (currentAtmosphereEntity == nullptr) {
            oAmount -= oc->getOxygenScale();
        }
        else {
            auto ac = currentAtmosphereEntity->getComponent<AtmosphereComponent>("atmosphere");
            oAmount += (ac->getOxygenModifier()*oc->getOxygenScale());
        }
        oc->setOxygenAmount(oAmount);

    }
}
