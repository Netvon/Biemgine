#include <algorithm>

#include "bmOxygenSystem.h"

namespace spacebiem
{
    void bmOxygenSystem::before()
    {
    }

    void bmOxygenSystem::update(const bmEntity & entity)
    {
        if (entity.hasComponent("atmosphere")) {
            auto ac = entity.getComponent<bmAtmosphereComponent*>("atmosphere");
            if (find(atmospheres.begin(), atmospheres.end(), ac) == atmospheres.end()) {
                atmospheres.push_back(ac);
            }
        }

        if (!entity.hasComponent("oxygen")) return;
        if (entity.hasComponent("ui")) return;

        auto oc = entity.getComponent<bmOxygenComponent*>("oxygen");

        bmAtmosphereComponent* currentAtmosphere = nullptr;
        if (entity.hasComponent("position")) {
            auto pc = entity.getComponent<bmPositionComponent*>("position");

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

    void bmOxygenSystem::after()
    {
    }

    void bmOxygenSystem::onSceneSwitch()
    {
    }
}
