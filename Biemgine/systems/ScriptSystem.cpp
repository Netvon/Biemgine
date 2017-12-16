#include "ScriptSystem.h"

namespace biemgine {
    void ScriptSystem::onAddEntity(Entity & entity)
    {
        auto script = entity.getComponent<ScriptComponent>("script");

        if (script != nullptr)
        {
            Entry entry;
            entry.entity = &entity;
            entry.scriptComponent = script;

            entries.push_back(std::move(entry));
        }
    }

    void ScriptSystem::update(const float deltaTime)
    {
        for (const auto& entry: entries)
        {
            entry.scriptComponent->run(deltaTime / 1000.f);
        }
    }
}
