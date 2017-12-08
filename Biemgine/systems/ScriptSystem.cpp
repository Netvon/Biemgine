#include "ScriptSystem.h"

namespace biemgine {

    void ScriptSystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("script"))
            return;

        auto script = entity.getComponent<ScriptComponent>("script");
        script->run();
    }

    System::required_components ScriptSystem::requirements() const
    {
        return {
            System::requirement<ScriptComponent>()
        };
    }
}
