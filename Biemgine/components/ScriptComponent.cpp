#include "ScriptComponent.h"

namespace biemgine {

    ScriptComponent::ScriptComponent(function<void(float)> pScript) : script(pScript)
    {

    }

    void ScriptComponent::run(float deltaTime)
    {
        script(deltaTime);
    }
}
