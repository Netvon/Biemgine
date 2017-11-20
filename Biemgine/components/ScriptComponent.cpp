#include "ScriptComponent.h"

namespace biemgine {

    ScriptComponent::ScriptComponent(function<void()> pScript) : script(pScript)
    {

    }

    void ScriptComponent::run()
    {
        script();
    }
}
