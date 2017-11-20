
#include "SaveBlobSystem.h"

using biemgine::StateManager;

namespace spacebiem
{
    SaveBlobSystem::SaveBlobSystem()
    {
        saveBlobFactory = new SaveBlobFactory();
    }

    SaveBlobSystem::~SaveBlobSystem()
    {
        delete saveBlobFactory;
    }

    void SaveBlobSystem::after(const float deltaTime)
    {
        if (savingBlob || !getStateManager()->getInputManager()->isKeyDown("S"))
            return;

        savingBlob = true;
        vector<string> saveBlob = saveBlobFactory->createFromEntities(getStateManager()->getEntities());

        FileHandler fileHandler("savegame.csv");

        for (auto it = saveBlob.begin(); it != saveBlob.end(); it++) {
            fileHandler.writeLine(*it);
        }

        savingBlob = false;
    }
}
