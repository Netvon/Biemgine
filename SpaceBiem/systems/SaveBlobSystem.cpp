
#include "SaveBlobSystem.h"

using biemgine::StateManager;

namespace spacebiem
{
    void SaveBlobSystem::update(const Entity & entity)
    {
        entities.push_back(&entity);
    }

    void SaveBlobSystem::after(const float deltaTime)
    {
        if (savingBlob || !getStateManager()->getInputManager()->isKeyDown("S")) {
            entities.clear();
            return;
        }

        savingBlob = true;
        vector<string> saveBlob = saveBlobFactory.createFromEntities(entities);
        entities.clear();

        FileHandler fileHandler("data/savegame.csv", true);

        for (auto it = saveBlob.begin(); it != saveBlob.end(); it++) {
            fileHandler.writeLine(*it);
        }

        savingBlob = false;
    }
}
