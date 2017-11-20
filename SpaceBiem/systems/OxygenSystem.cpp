#include <algorithm>

#include "OxygenSystem.h"

using biemgine::PositionComponent;

namespace spacebiem
{
    void OxygenSystem::before()
    {
    }

    void OxygenSystem::update(const Entity & entity)
    {
        if (entity.hasComponent("atmosphere")) {
            auto ac = entity.getComponent<AtmosphereComponent*>("atmosphere");
            if (find(atmospheres.begin(), atmospheres.end(), ac) == atmospheres.end()) {
                atmospheres.push_back(ac);
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

        if (!entity.hasComponent("oxygen")) return;
        if (entity.hasComponent("ui")) return;

        auto oc = entity.getComponent<OxygenComponent*>("oxygen");

        AtmosphereComponent* currentAtmosphere = nullptr;
        if (entity.hasComponent("position")) {
            auto pc = entity.getComponent<PositionComponent*>("position");

            for (auto atmos : atmospheres) {
                int xA = static_cast<int>(atmos->getX());
                int yA = static_cast<int>(atmos->getY());
                int rA = static_cast<int>(atmos->getRadius());
                int x = static_cast<int>(pc->getX());
                int y = static_cast<int>(pc->getY());

                // Kei skône pietjegras theorie
                if (((x - xA)*(x - xA)) + ((y - yA)*(y - yA)) <= (rA*rA)) {
                    currentAtmosphere = atmos;
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

    void OxygenSystem::after()
    {
    }

    void OxygenSystem::onSceneSwitch()
    {
    }
}
