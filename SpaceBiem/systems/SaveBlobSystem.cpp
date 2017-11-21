
#include "SaveBlobSystem.h"

using biemgine::StateManager;

namespace spacebiem
{
    void SaveBlobSystem::after(const float deltaTime)
    {
        if (savingBlob || !getStateManager()->getInputManager()->isKeyDown("S"))
            return;

        savingBlob = true;
        auto& e = getStateManager()->getEntities();
        vector<string> saveBlob = saveBlobFactory.createFromEntities(e);

        FileHandler fileHandler("data/savegame.csv", true);

        for (auto it = saveBlob.begin(); it != saveBlob.end(); it++) {
            fileHandler.writeLine(*it);
        }

        savingBlob = false;
    }
}
