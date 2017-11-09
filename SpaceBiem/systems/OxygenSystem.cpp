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

        if (!entity.hasComponent("oxygen")) return;
        if (entity.hasComponent("ui")) return;

        auto oc = entity.getComponent<OxygenComponent*>("oxygen");

        AtmosphereComponent* currentAtmosphere = nullptr;
        if (entity.hasComponent("position")) {
            auto pc = entity.getComponent<PositionComponent*>("position");

            for (auto atmos : atmospheres) {
                int xA = atmos->getX();
                int yA = atmos->getY();
                int rA = atmos->getRadius();
                int x = pc->getX();
                int y = pc->getY();

                // Kei skône pietjegras theorie
                if (((x - xA)*(x - xA)) + ((y - yA)*(y - yA)) <= (rA*rA)) {
                    currentAtmosphere = atmos;
                    break;
                }
            }
        }

        int oAmount = oc->getOxygenAmount();
        if (currentAtmosphere == nullptr) {
            oAmount -= oc->getOxygenDecrease();
        }
        else {
            oAmount += oc->getOxygenIncrease();
        }
        oc->setOxygenAmount(oAmount);

        if (oAmount <= 0) {
            // TODO: fix
            // transitionManager->gameOverTransition();
        }
    }

    void OxygenSystem::after()
    {
    }

    void OxygenSystem::onSceneSwitch()
    {
    }
}
