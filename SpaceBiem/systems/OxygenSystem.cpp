#include <algorithm>

#include "OxygenSystem.h"

using biemgine::PositionComponent;

namespace spacebiem
{
    void OxygenSystem::update(const Entity & entity)
    {
        if (entity.hasComponent("atmosphere")) {
            auto ac = entity.getComponent<AtmosphereComponent>("atmosphere");
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

        auto oc = entity.getComponent<OxygenComponent>("oxygen");

        std::shared_ptr<AtmosphereComponent> currentAtmosphere = nullptr;
        if (entity.hasComponent("position")) {
            auto pc = entity.getComponent<PositionComponent>("position");

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

        float oAmount = oc->getOxygenAmount();
        if (currentAtmosphere == nullptr) {
            oAmount -= oc->getOxygenScale();
        }
        else {
            oAmount += (currentAtmosphere->getOxygenModifier()*oc->getOxygenScale());
        }
        oc->setOxygenAmount(oAmount);

    }

    System::required_components OxygenSystem::requirements() const
    {
        return {
            System::requirement<AtmosphereComponent, System::optional>(),
            System::requirement<biemgine::UIComponent, System::exclude>(),
        };
    }
}
