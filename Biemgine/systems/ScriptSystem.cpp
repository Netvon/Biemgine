#include "ScriptSystem.h"

namespace biemgine {

    void ScriptSystem::update(const Entity & entity, const float deltaTime)
    {
        if (!entity.hasComponent("script"))
            return;

        auto script = entity.getComponent<ScriptComponent>("script");
        script->run(deltaTime / 1000.f);
    }
}
