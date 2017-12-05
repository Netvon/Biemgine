#include <algorithm>

#include "OxygenSystem.h"

using biemgine::PositionComponent;

namespace spacebiem
{
    void OxygenSystem::update(const Entity & entity)
    {
        if (entity.hasComponent("atmosphere")) {
            std::find(entitiesWithAtmospheres.begin(), entitiesWithAtmospheres.end(), entity);
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

        if (!entity.hasComponent("oxygen")) return;
        if (entity.hasComponent("ui")) return;

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
